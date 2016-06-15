#include "authorization.h"
#include <QWebView>
#include <QVBoxLayout>
#include <QUrlQuery>

#include <config.h>
#include <request.h>

Authorization::Authorization(QDialog *parent) : QDialog(parent)
{
    readToken();
    if (!needGui())
        return;

    QWebView* view = new QWebView(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    setWindowTitle("Authorization");

    connect( view, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)) );

    view->load(QUrl("https://oauth.vk.com/authorize?client_id=5453408&redirect_uri=https://oauth.vk.com/blank.html&scope=offline,status,messages,friends,wall,audio,photos&display=wap&response_type=token"));
}

void Authorization::urlChanged(const QUrl& url1)
{
    QUrl url = url1.toString().replace("#","?");

    QUrlQuery query(url);
    auto token = query.queryItemValue("access_token");
    if ( !token.isEmpty() )
    {
        Config::getInstance().setToken(token);
        token_ = token;
        Config::getInstance().setUserId(query.queryItemValue("user_id").toLongLong());
        close();
    }
}

void Authorization::readToken()
{
    auto& config = Config::getInstance();
    auto token = config.getToken();
    if (token.isEmpty())
        return;

    auto request = request::create(request::urlFriendsGet,
                   { {"v","5.8"},
                     {"fields","first_name,last_name"} } );
    auto answer = request::get(request);

    if ( !answer.isEmpty() && answer.toStdString().find("error_code") == std::string::npos )
    {
        token_= token;
        return;
    }

    config.setToken("");
}

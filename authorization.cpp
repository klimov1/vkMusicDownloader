#include "authorization.h"
#include <QWebView>
#include <QVBoxLayout>
#include <QUrlQuery>

#include <config.h>
#include <request.h>

Authorization::Authorization(QDialog *parent) : QDialog(parent)
{
    readToken();
    if (hasValidToken())
        return;

    QWebView* view = new QWebView(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    setWindowTitle("Authorization");

    connect( view, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)) );

    // probably I don't need such a big scope... maybe someday..
    view->load(QUrl("https://oauth.vk.com/authorize?client_id=5453408&redirect_uri=https://oauth.vk.com/blank.html&scope=offline,status,messages,friends,wall,audio,photos&display=wap&response_type=token"));
}

bool Authorization::hasValidToken() const
{
    return !Config::getInstance().getToken().isEmpty();
}

void Authorization::urlChanged(const QUrl& url1)
{
    // for some reasone vk team decided to send '#' instead of '?'
    QUrl url = url1.toString().replace("#","?");

    QUrlQuery query(url);
    auto token = query.queryItemValue("access_token");
    if ( !token.isEmpty() )
    {
        Config::getInstance().setToken(token);        
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

    // check that token is valid
    auto request = request::create(request::urlFriendsGet,
                   { {"v","5.8"},
                     {"fields","first_name,last_name"} } );
    auto answer = request::get(request);

    if ( !answer.isEmpty() && answer.toStdString().find("error_code") == std::string::npos )
    {
        config.setToken(token);
        return;
    }

    config.setToken("");
}

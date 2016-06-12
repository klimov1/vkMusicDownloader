#include "request.h"
#include "config.h"

#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QTimer>
#include <QDebug>

namespace request {

QUrl create(const QUrl& url, const ParamList &params, bool defaultToken)
{
    QUrlQuery qurl(url);
    for (auto& it : params)
        qurl.addQueryItem(it.first, it.second);

    qurl.addQueryItem("v","5.8");
    if ( defaultToken && !Config::getInstance().getToken().isEmpty())
        qurl.addQueryItem("access_token", Config::getInstance().getToken());

    return url.toString() + qurl.query();
}

QByteArray get(const QUrl &url, int wait)
{
    qDebug() << "get " << url;
    QNetworkAccessManager* manager = new QNetworkAccessManager() ;
    QNetworkReply* reply = manager->get(QNetworkRequest( url ));

    QEventLoop waitLoop;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),&waitLoop,SLOT(quit()));
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)),&waitLoop,SLOT(deleteLater()));
    QTimer::singleShot(wait,&waitLoop,SLOT(quit()));

    waitLoop.exec();

    QByteArray answer = reply->readAll();
    reply->deleteLater();
    return answer;
}

} // request

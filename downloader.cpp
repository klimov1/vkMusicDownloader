#include "downloader.h"


Downloader::Downloader(QObject *parent) : QObject(parent)
{
    accessMgr_ = new QNetworkAccessManager(this);
    connect(accessMgr_, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedLoad(QNetworkReply*)));
}

Downloader::~Downloader()
{
    qDebug() << "Destroyed " << this;
}

void Downloader::download(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply* reply = accessMgr_->get(request);

    connect(reply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(progress(qint64,qint64)));
    connect(this, SIGNAL(destroyed(QObject*)), reply, SLOT(deleteLater()));

}

void Downloader::finishedLoad(QNetworkReply *reply)
{
    if ( reply->error() != QNetworkReply::NoError )
        emit error();
    else
        emit done(reply->readAll());

    reply->deleteLater();
}

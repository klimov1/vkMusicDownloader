#include "downloader.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class Downloader::DownloaderGui : public QObject
{
    Q_OBJECT

public:
    DownloaderGui() : QObject(nullptr)
    {
        accessMgr_ = new QNetworkAccessManager(this);
        connect(accessMgr_, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedLoad(QNetworkReply*)));
    }

    void download(const QUrl& url)
    {
        QNetworkRequest request(url);
        QNetworkReply* reply = accessMgr_->get(request);
        //connect(reply, )
    }

signals:
    //void downloadProgress()

private slots:
    void finishedLoad(QNetworkReply* reply)
    {

    }

private:
    QNetworkAccessManager* accessMgr_;
};

Downloader::Downloader() : gui_(new DownloaderGui())
{
}

Downloader::~Downloader()
{}

Downloader &Downloader::getInstance()
{
    static Downloader loader;
    return loader;
}

void Downloader::addToQueue(const QString &saveToFile, const QUrl &url)
{

}


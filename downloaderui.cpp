#include "downloaderui.h"
#include <QGridLayout>
#include <QFile>

//test code
QString tempName;

DownloaderUI::DownloaderUI() : QWidget(nullptr)
{
    // the downloader itself
    loader_ = new Downloader();

    // gui stuff
    pBar_ = new QProgressBar(this);

    connect(loader_, SIGNAL(progress(qint64,qint64)), this, SLOT(progress(qint64,qint64)));
    connect(loader_, SIGNAL(done(QUrl,QByteArray)), this, SLOT(done(QUrl,QByteArray)));

    QGridLayout* layout = new QGridLayout();
    layout->addWidget(pBar_);
    setLayout(layout);
}

DownloaderUI::~DownloaderUI()
{
    qDebug() << "DownloaderUI destroyed";
    delete loader_;
}

void DownloaderUI::load(const QString &saveToFile, const QUrl &url)
{
    loader_->download(url);
    tempName = saveToFile;
}

void DownloaderUI::error()
{
    qDebug() << "Error raised";
}

void DownloaderUI::progress(qint64 bytesReceived, qint64 bytesTotal)
{
    if ( bytesTotal <= 0)
    {
        qDebug() << "Less than a 0 bytes total. Something is wrong";
        error();
        return;
    }
    pBar_->setValue(100*bytesReceived/bytesTotal);
}

void DownloaderUI::done(const QUrl &url, const QByteArray &data)
{
    QFile file(tempName);
    if ( !file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Cannot open a file < " << tempName << ">";
        return;
    }
    file.write(data);
    file.close();

    qDebug() << "Done. File saved to " << tempName;
    this->deleteLater();
}

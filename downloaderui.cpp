#include "downloaderui.h"
#include <QGridLayout>
#include <QFile>


DownloaderUI::DownloaderUI(QWidget *parent, const QUrl& url, const QString& saveToFile ) :
    QWidget(parent), fileName_(saveToFile)
{
    // the downloader itself
    loader_ = new Downloader(this);

    // gui stuff

    // progress bar connections
    pBar_ = new QProgressBar(this);   
    connect(loader_, SIGNAL(progress(qint64,qint64)), this, SLOT(progress(qint64,qint64)));
    connect(loader_, SIGNAL(done(QByteArray)), this, SLOT(done(QByteArray)));

    fileNameLbl_ = new QLabel(saveToFile, this);
    stopBtn_ = new QPushButton("Cancel", this);

    // delete widget if Cancel pressed
    connect(stopBtn_, QPushButton::clicked, this,[&](bool){
        this->deleteLater();
    });

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(fileNameLbl_);

    QHBoxLayout* horizLayout = new QHBoxLayout();
    horizLayout->addWidget(pBar_);
    horizLayout->addWidget(stopBtn_);

    layout->addItem(horizLayout);

    setLayout(layout);

    // start loading...
    loader_->download(url);
}

DownloaderUI::~DownloaderUI()
{
    qDebug() << "DownloaderUI destroyed";
}

void DownloaderUI::error()
{
    qDebug() << "Something wrong with downloading. Error raised";
}

void DownloaderUI::progress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal <= 0)
    {        
        error();
        return;
    }
    pBar_->setValue(100*bytesReceived/bytesTotal);
}

void DownloaderUI::done(const QByteArray &data)
{
    QFile file(fileName_);
    if ( !file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Cannot open a file < " << fileName_ << ">";
        return;
    }
    file.write(data);
    file.close();

    qDebug() << "Done. File saved to " << fileName_;
    this->deleteLater();
}

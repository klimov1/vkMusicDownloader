#include "downloadmanager.h"
#include "downloaderui.h"

DownloadManager* DownloadManager::instance_s = nullptr;

DownloadManager::DownloadManager() : QWidget(nullptr)
{
    mainLayout_ = new QVBoxLayout(this);
    setLayout(mainLayout_);
    setBaseSize(300,150);

    show();

    setAttribute( Qt::WA_DeleteOnClose );
}

DownloadManager::~DownloadManager()
{
    qDebug() << "DownloadManager destroyed";
    instance_s = nullptr;
}

DownloadManager& DownloadManager::getInstance()
{
    if (!instance_s)
        instance_s = new DownloadManager();

    return *instance_s;
}

void DownloadManager::addToQueue(const QString &saveToFile, const QUrl &url)
{
    mainLayout_->addWidget(new DownloaderUI(this, url, saveToFile));
}

#include "downloadmanager.h"
#include "downloaderui.h"

DownloadManager::DownloadManager() //: gui_(new DownloadManagerGui())
{
}

DownloadManager::~DownloadManager()
{}

DownloadManager &DownloadManager::getInstance()
{
    static DownloadManager loader;
    return loader;
}

void DownloadManager::addToQueue(const QString &saveToFile, const QUrl &url)
{
    DownloaderUI* ptr = new DownloaderUI();
    ptr->show();
    ptr->load(saveToFile,url);
}

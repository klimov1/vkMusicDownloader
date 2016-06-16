#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QString>
#include <QUrl>
#include <memory>

class DownloadManager
{
    DownloadManager();
public:
    DownloadManager(const DownloadManager&) = delete;
    DownloadManager(DownloadManager&&) = delete;
    ~DownloadManager();

    static DownloadManager& getInstance();
    void addToQueue( const QString& saveToFile, const QUrl& url);

/*private:
    class DownloadManagerGui;
    std::unique_ptr<DownloadManagerGui> gui_;*/
};

#endif // DOWNLOADMANAGER_H

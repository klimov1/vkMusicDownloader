#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QString>
#include <QUrl>
#include <memory>

class Downloader
{
    Downloader();  
public:
    Downloader(const Downloader&) = delete;
    Downloader(Downloader&&) = delete;
    ~Downloader();

    static Downloader& getInstance();
    void addToQueue( const QString& saveToFile, const QUrl& url);

private:
    class DownloaderGui;
    std::unique_ptr<DownloaderGui> gui_;
};

#endif // DOWNLOADER_H

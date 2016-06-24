#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QString>
#include <QUrl>
#include <QWidget>
#include <QVBoxLayout>

//
// Basically it's a holder of all dowload widgets
//
class DownloadManager : public QWidget
{
    DownloadManager();
public:
    DownloadManager(const DownloadManager&) = delete;
    DownloadManager(DownloadManager&&) = delete;
    ~DownloadManager();

    static DownloadManager& getInstance();

    // load asynchronously
    void addToQueue(const QString& saveToFile, const QUrl& url);

private:
    QVBoxLayout* mainLayout_ = nullptr;

private:
    // need it to get the only one window with progressbars. see getInstance
    static DownloadManager* instance_s;
};

#endif // DOWNLOADMANAGER_H

#ifndef DOWNLOADERUI_H
#define DOWNLOADERUI_H

#include "downloader.h"

#include <QWidget>
#include <QProgressBar>
#include <QLineEdit>
#include <QPushButton>

class DownloaderUI : public QWidget
{
    Q_OBJECT
public:
    DownloaderUI();
    ~DownloaderUI();

    //test code for now
    void load(const QString &saveToFile, const QUrl &url);

signals:

private slots:
    //void start();
    void error();
    void progress(qint64 bytesReceived, qint64 bytesTotal);
    void done(const QUrl& url, const QByteArray& data);

private:
    // the downloader itself
    Downloader* loader_;

    // gui stuff
    QProgressBar* pBar_;
    //QLineEdit* edit_;

    //std::vector<Do
};

#endif // DOWNLOADERUI_H

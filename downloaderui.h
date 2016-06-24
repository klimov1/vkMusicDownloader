#ifndef DOWNLOADERUI_H
#define DOWNLOADERUI_H

#include "downloader.h"

#include <QWidget>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>

//
// Downloader GUI representation.
// as usuall for this kind of forms, it has a progress bar and Cancel button
//
class DownloaderUI : public QWidget
{
    Q_OBJECT
public:
    DownloaderUI(QWidget* parent, const QUrl& url, const QString& saveToFile );
    ~DownloaderUI();

private slots:
    void error();
    void progress(qint64 bytesReceived, qint64 bytesTotal);
    void done(const QByteArray& data);

private:
    // the downloader itself
    Downloader* loader_ = nullptr;
    // save song with this name
    QString fileName_;

private:
    // gui stuff
    QProgressBar* pBar_ = nullptr;
    QLabel* fileNameLbl_ = nullptr;
    QPushButton* stopBtn_ = nullptr;
};

#endif // DOWNLOADERUI_H

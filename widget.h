#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QString>
#include <QByteArray>
#include <QTimer>
#include <QEventLoop>

namespace Ui {
class Widget;
}

struct User
{
    qlonglong id_;
    QString firstName_;
    QString lastName_;
    QString domain_;
    bool isOnline_;
};


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void authSuccess();

public slots:
    void checkUrl(QUrl url);
    void getFriends();

private slots:

    void on_getAudiosBtn_clicked();

private:
    QByteArray GET(QUrl url);

    void saveToken();
    void readToken();

private:
    Ui::Widget *ui;
    QString token_;
    int songCount_ = 50;
};

#endif // WIDGET_H

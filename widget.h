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

private slots:

    void on_getAudiosBtn_clicked();
    void songCountChanged(QString);

private:
    Ui::Widget *ui;
    int songCount_ = 50;
};

#endif // WIDGET_H

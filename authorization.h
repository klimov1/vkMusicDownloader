#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include <QString>
#include <QUrl>

class Authorization : public QDialog
{
    Q_OBJECT
public:
    explicit Authorization(QDialog *parent = 0);

    QString getToken()const { return token_; }
    bool needGui()const { return token_.isEmpty(); }
    bool hasToken()const { return !token_.isEmpty(); }

public slots:
    void urlChanged(const QUrl& url);

private:
    void readToken();

private:
    QString token_;
    qint64 userId_;
};

#endif // AUTHORIZATION_H

#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QDialog>
#include <QString>
#include <QUrl>

//
// authorization form.
// reads and writes to Config instance
//
class Authorization : public QDialog
{
    Q_OBJECT
public:
    explicit Authorization(QDialog *parent = 0);

    // do we have a valid token to continue?
    bool hasValidToken()const;

private slots:
    void urlChanged(const QUrl& url);

private:
    void readToken();
};

#endif // AUTHORIZATION_H

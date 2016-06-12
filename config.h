#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QVariantMap>

class Config
{
public:
    Config(const Config&) = delete;
    Config(Config&&) = delete;
    ~Config();

    // the only accessor
    static Config& getInstance();

    QString getToken()const;
    void setToken(const QString& token);

    qlonglong getUserId()const;
    void setUserId( qlonglong userId);
private:
    Config();

private:
    QVariantMap settings_;
};

#endif // CONFIG_H

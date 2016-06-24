#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QVariantMap>

//
// holds all configs that we need
//
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
    // settings holder
    QVariantMap settings_;
};

#endif // CONFIG_H

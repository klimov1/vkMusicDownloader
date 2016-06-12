#include "config.h"
#include <QFile>
#include <QDataStream>

namespace
{
    QString fileName = "config.txt";
}

Config::Config()
{
    QFile file(fileName);
    if( !file.open(QFile::ReadOnly) )
        return;

    QDataStream stream(&file);
    stream >> settings_;
}

Config::~Config()
{
    QFile file(fileName);
    if( !file.open(QFile::WriteOnly | QFile::Truncate) )
        return;

    QDataStream stream(&file);
    stream << settings_;
}

Config &Config::getInstance()
{
    static Config conf;
    return conf;
}

QString Config::getToken() const
{
     return settings_["access_token"].toString();
}

void Config::setToken(const QString &token)
{
    settings_["access_token"] = token;
}

qlonglong Config::getUserId() const
{
    return settings_["user_id"].toLongLong();
}

void Config::setUserId(qlonglong userId)
{
    settings_["user_id"] = userId;
}

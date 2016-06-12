#ifndef REQUEST_H
#define REQUEST_H

#include <map>
#include <QString>
#include <QUrl>
#include <QByteArray>

namespace request {

    const QString urlFriendsGet = "https://api.vk.com/method/friends.get?";
    const QString urlAudioGet = "https://api.vk.com/method/audio.get?";



    using ParamList = std::map<QString, QString>;
    QUrl create(const QUrl &url, const ParamList& params, bool defaultToken = true );

    // get request. returns response as byte array
    QByteArray get(const QUrl& url, int wait = 10000);
}

#endif // REQUEST_H

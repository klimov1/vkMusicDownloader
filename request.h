#ifndef REQUEST_H
#define REQUEST_H

#include <map>
#include <QString>
#include <QUrl>
#include <QByteArray>

namespace request {

    // short hands for common requests
    const QString urlFriendsGet = "https://api.vk.com/method/friends.get?";
    const QString urlAudioGet = "https://api.vk.com/method/audio.get?";

    // Params:
    // url - url for concatination
    // params - params to add
    // defaultToken - if true - add 'access_token' key from config, false - otherwise
    using ParamList = std::map<QString, QString>;
    QUrl create(const QUrl &url, const ParamList& params, bool defaultToken = true );

    // get request. returns response as byte array    
    QByteArray get(const QUrl& url, int wait = 10000);

} // request

#endif // REQUEST_H

#include "audio.h"
#include "request.h"
#include "utils.h"

#include <QJsonArray>
#include <QJsonObject>

#include <QDebug>
namespace audio {

std::vector<SongInfo> getSongs(qlonglong userId, std::size_t count)
{
    auto url = request::create(request::urlAudioGet, { {"owner_id", utils::toString(userId)},
                                                       {"count", utils::toString(count)}} );
    auto js = utils::convertJson( request::get(url) );

    std::vector<SongInfo> songs;
    songs.reserve( static_cast<std::size_t>( js["count"].toDouble() ) );

    auto itemArray = js["items"].toList();
    for (const auto& listIt : itemArray)
    {
        auto it = listIt.toMap();

        SongInfo song;
        song.artist_ = it["artist"].toString();
        song.duration_ =  it["duration"].toDouble();
        song.id_ = static_cast<qlonglong>(it["id"].toDouble());
        song.ownerId_ = static_cast<qlonglong>(it["owner_id"].toDouble());
        song.title_ = it["title"].toString();
        song.url_ = it["url"].toString();

        songs.push_back(song);

    }

    return songs;
}

}

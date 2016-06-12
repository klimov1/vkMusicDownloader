#ifndef AUDIO_H
#define AUDIO_H

#include <vector>
#include <QString>
#include <QUrl>

namespace audio {

struct SongInfo
{
    qlonglong id_;
    qlonglong ownerId_;
    QString artist_;
    QString title_;
    double duration_;
    QUrl url_;
};

std::vector<SongInfo> getSongs(qlonglong userId, std::size_t count = 50);

}

#endif // AUDIO_H

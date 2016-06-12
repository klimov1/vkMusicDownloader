#include "widget.h"
#include <QApplication>

#include "authorization.h"
#include "audio.h"
#include "config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Authorization author;
    if( author.needGui() )
        author.exec();

    auto token = author.getToken();
    if (token.isEmpty())
        return -1;

/*    auto songsList = audio::getAllSongs(Config::getInstance().getUserId());

    for ( auto& it : songsList )
        qDebug() << it.artist_ << " - " << it.title_ << " : " << it.duration_;

    return 0;*/

    Widget w;
    w.show();

    return a.exec();
}

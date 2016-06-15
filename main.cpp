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

    if (!author.hasToken())
        return -1;

    Widget w;
    w.show();

    return a.exec();
}

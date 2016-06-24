#include <QApplication>

#include "authorization.h"
#include "audio.h"
#include "config.h"

#include "mainview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // authorization first
    Authorization authorizationGui;
    if( !authorizationGui.hasValidToken() )
        authorizationGui.exec();

    // did we get a valid token?
    if (!authorizationGui.hasValidToken())
        return -1;

    MainView view;
    view.show();

    return a.exec();
}

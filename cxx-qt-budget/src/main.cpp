#include <QApplication>
// #include <QDesktopWidget>
#include <QScreen>

#include "mainframe.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QScreen* screen = QGuiApplication::primaryScreen();
    // QRect screenGeometry = screen->geometry();

    (new CMainFrame())->showNormal();

    return QApplication::exec();
}
#include "mainwindow.h"

#include <QApplication>
#include  <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    // Calculate the center position for the window
    int x = (screenGeometry.width() - w.width()) / 2;
    int y = (screenGeometry.height() - w.height()) / 2;

    // Move the window to the centered position
    w.move(x,y);

    w.show();
    w.setWindowTitle("Whilone");
    return a.exec();
}

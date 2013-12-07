#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Luna Project");
    app.setApplicationName("Device IP Scan");
    MainWindow w;
    w.show();

    return app.exec();
}

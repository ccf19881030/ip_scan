#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Luna");
    app.setApplicationName("Device IP Scan");
    MainWindow w;
    w.setWindowTitle("Luna scanner");
    w.show();

    return app.exec();
}

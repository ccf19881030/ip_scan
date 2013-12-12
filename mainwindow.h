#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QMovie>

#include "shellprocess.h"
#define THREAD_SIZE 100

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ShellProcess *shellProcess;

private slots:    

    void startScan(); // Execute when 'scan' button clicked.

public slots:
    void onPingComplete();
    void onPingSuccess(QString ip);
    void onPingFailed(QString ip);

private:
    Ui::MainWindow *ui;
    QProcess *myProcess;
    QMovie *loadingImage;


    QString get_localmachine_ip();
    QStringList generateRangeIP(QString ip1, QString ip2);
    QStringList scanHosts;
    int onlineCount;
};

#endif // MAINWINDOW_H

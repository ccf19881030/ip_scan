#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QMovie>

#include "shellprocess.h"
#include "device.h"

#define THREAD_SIZE 10

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
    void on_showOnlineDevicesButton_clicked();

    void on_testSSH_Button_clicked();

public slots:
    void onCommandSuccess(QString ip);
    void onCommandFailed(QString ip);
    //更新当前扫描ip的进度
    void update_scanProgress(QString ip);

private:
    Ui::MainWindow *ui;
    QProcess *myProcess;
    QMovie *loadingImage;


    QString get_localmachine_ip();
    QStringList generateRangeIP(QString ip1, QString ip2);
    QStringList scanHosts;
    QStringList to_scanHosts;
    QStringList onlineHosts;

    QVector<Device*> _onlineDevices;

    int onlineCount;

    double currentScanNum;//扫描的进度
    double totalScanNum;//总的IP扫描数目
};

#endif // MAINWINDOW_H

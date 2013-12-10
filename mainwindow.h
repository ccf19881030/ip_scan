#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

#include "shellprocess.h"

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
    void startExecuteCommand();
    void printOutput();
    void printError();
    void startScan();

    void on_pushButton_shell_run_clicked();

public slots:
    void onPingComplete();
    void onPingSuccess(QString ip);
    void onPingFailed(QString ip);

private:
    Ui::MainWindow *ui;
    QProcess *myProcess;

    QString get_localmachine_ip();
    QStringList generateRangeIP(QString ip1, QString ip2);

};

#endif // MAINWINDOW_H

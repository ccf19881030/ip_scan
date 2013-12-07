#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void startScan();

private:
    Ui::MainWindow *ui;
    QString get_localmachine_ip();
    QStringList generateRangeIP(QString ip1, QString ip2);

};

#endif // MAINWINDOW_H

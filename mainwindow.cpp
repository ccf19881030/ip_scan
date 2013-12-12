#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QTableView>
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    onlineCount = 0;
    ui->setupUi(this);
    ui->tableWidget->setWindowTitle("ip list");
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 120);
    ui->tableWidget->setColumnWidth(1, 200);

    QStringList header;
     header.append(QObject::tr("IP"));
     header.append(QObject::tr("Connected?"));
     header.append("");
     ui->tableWidget->setHorizontalHeaderLabels(header);
     ui->tableWidget->setShowGrid(true);
     ui->tableWidget->setStyleSheet("selection-background-color:lightblue;");

     ui->tableWidget->horizontalHeader()->setStretchLastSection(true);     

     connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(startScan()));


     QString localIP = this->get_localmachine_ip();
     QStringList localIPList = localIP.split(".");
     // set default value.
     ui->lineEdit->setText(localIPList[0]+"."+localIPList[1]+"."+localIPList[2]+".1");
     ui->lineEdit_2->setText(localIPList[0]+"."+localIPList[1]+"."+localIPList[2]+".254");
     ui->label_local_ip->setText(localIP);
     loadingImage = new QMovie(":/images/loading.gif");
     ui->loadingLabel->setMovie(loadingImage);
}

void MainWindow::onPingSuccess(QString ip) {
    qDebug() << ip + " ping success";

    int hostIndex = scanHosts.indexOf(ip);

    QTableWidgetItem *statusItem = new QTableWidgetItem();
    statusItem->setIcon(QIcon(":/images/online_icon.png"));
    ui->tableWidget->setItem(hostIndex,1,statusItem);
    onlineCount++;

    ui->onlineCount_label->setText(QString::number(onlineCount));


}
void MainWindow::onPingFailed(QString ip) {
    qDebug() << ip + " ping failed";

    int hostIndex = scanHosts.indexOf(ip);
    QTableWidgetItem *statusItem = new QTableWidgetItem();
    statusItem->setIcon(QIcon(":/images/offline_icon.png"));
    ui->tableWidget->setItem(hostIndex,1,statusItem);

    qDebug() << ip + " ping failed 111111";
}

void MainWindow::onPingComplete() {
    loadingImage->stop();
    ui->loadingLabel->hide();
    qDebug() << "handle Result";

    QMessageBox msgBox;
    msgBox.setText("All ping completed.");
    msgBox.exec();
}

void MainWindow::startScan() {

    QString ip1 = ui->lineEdit->text();
    QString ip2 = ui->lineEdit_2->text();
    QStringList ip1List = ip1.split(".");
    QStringList ip2List = ip2.split(".");

    if(ip1List.length() != 4){
        QMessageBox msgBox;
        msgBox.setText("Beginning ip not valid!");
        msgBox.exec();
        ui->lineEdit->setFocus();
        return;
    }

    if(ip2List.length() != 4){
        QMessageBox msgBox;
        msgBox.setText("Endding ip not valid!");
        msgBox.exec();
        ui->lineEdit_2->setFocus();
        return;
    }

    if(ip1List[0] != ip2List[0] || ip1List[1] != ip2List[1]) {
        QMessageBox msgBox;
        msgBox.setText("IP range must be in same lan!");
        msgBox.exec();
        ui->lineEdit_2->setFocus();
        return;
    }

    if(ip1List[2].toInt() > ip2List[2].toInt()) {
        QMessageBox msgBox;
        msgBox.setText("IP range not correct!");
        msgBox.exec();
        ui->lineEdit_2->setFocus();
        return;
    }else{
        if(ip1List[2].toInt() == ip2List[2].toInt()) {
            if(ip1List[3].toInt() >= ip2List[3].toInt()) {
                QMessageBox msgBox;
                msgBox.setText("IP range not correct!");
                msgBox.exec();
                ui->lineEdit_2->setFocus();
                return;
            }
        }else {

        }
    }

    if(ip1List[3].toInt() >= 255 || ip2List[3].toInt() >= 255 ){
        QMessageBox msgBox;
        msgBox.setText("IP not valid!");
        msgBox.exec();
        return;
    }    

    QStringList ipRange;
    if(ip1List[2].toInt() == ip2List[2].toInt()){
        // 192.168.3.1 -> 192.168.3.240
        int startIPNumber = ip1List[3].toInt();
        int endIPNumber   = ip2List[3].toInt();
        for(int i=startIPNumber;i <= endIPNumber;++i){
            QString ip = ip1List[0] + "." + ip1List[1] + "." + ip1List[2] + "." + QString::number(i);
            ipRange << ip;
        }
    } else if(ip1List[2].toInt() < ip2List[2].toInt()){
        // 192.168.3.1 -> 192.168.5.240
        int startIPNumber = ip1List[2].toInt();
        int endIPNumber   = ip2List[2].toInt();
        int j=0;
        for(int i = startIPNumber;i <= endIPNumber; ++i){
            if(i == startIPNumber){
                for(j=ip1List[3].toInt();j <= 254;++j){
                    QString ip = ip1List[0] + "." + ip1List[1] + "." + QString::number(i) + "." + QString::number(j);
                    ipRange << ip;
                }
            } else if(i == endIPNumber){
                for(j = 2; j <= ip2List[3].toInt(); ++j){
                    QString ip = ip1List[0] + "." + ip1List[1] + "." + QString::number(i) + "." + QString::number(j);
                    ipRange << ip;
                }
            } else {
                for(j = 2; j <= 254; ++j){
                    QString ip = ip1List[0] + "." + ip1List[1] + "." + QString::number(i) + "." + QString::number(j);
                    ipRange << ip;
                }
            }
        }
    }

    QString messageTip = "开始从IP "+ ip1 + "扫描到 " + ip2 + " ?";
    QMessageBox msgBox;
    msgBox.setWindowTitle("扫描IP");
    msgBox.setText(messageTip);
    msgBox.setStandardButtons(QMessageBox::No|QMessageBox::Yes);
    msgBox.setDefaultButton(QMessageBox::Yes);
    if(msgBox.exec() == QMessageBox::Yes){
        qDebug() << "Yes was clicked";
        this->scanHosts = ipRange;
        ui->tableWidget->setRowCount(ipRange.size());      
        for(int row_index=0;row_index<ipRange.size();++row_index) {
            ui->tableWidget->setItem(row_index,0,new QTableWidgetItem(ipRange[row_index]));
        }

        int ipArraySize = ipRange.size();
        int perIPArraySize = ipArraySize / THREAD_SIZE;
        qDebug() << "ip in one thread size: " << perIPArraySize;
        int start_outer = 0;
        int start_innerer = 0;
        QStringList ip_in_thread[THREAD_SIZE];
        for(start_outer;start_outer<THREAD_SIZE;++start_outer){
            for(start_innerer =  start_outer*perIPArraySize;start_innerer< (start_outer+1) * perIPArraySize;start_innerer++) {
                ip_in_thread[start_outer] << ipRange[start_innerer];
            }
            qDebug() << "##### " << start_outer ;
            qDebug() << " ---- " << ip_in_thread[start_outer] << " .";
        }

        qDebug() << "start_innerer " << start_innerer ;
        qDebug() << "start_outer " << start_outer ;

        for(int new_start=start_innerer, thread_index=0;new_start<ipArraySize;new_start++){
           qDebug() << " ---- " << ipRange[new_start] << " .";
           ip_in_thread[thread_index] << ipRange[new_start];
           thread_index++;
        }

        ShellProcess *shellProcess;
        for(int i=0;i<THREAD_SIZE;i++){
            shellProcess= new ShellProcess(this);
            connect(shellProcess, SIGNAL(pingCompleted()), this, SLOT(onPingComplete()));
            connect(shellProcess, SIGNAL(pingFailed(QString)), this, SLOT(onPingFailed(QString)));
            connect(shellProcess, SIGNAL(pingSuccess(QString)), this, SLOT(onPingSuccess(QString)));
            connect(shellProcess, SIGNAL(finished()), shellProcess, SLOT(deleteLater()));
            shellProcess->setIpRange(ip_in_thread[i]);
            shellProcess->start();
        }

        ui->loadingLabel->show();
        loadingImage->start();

    }else {
      // do something else
        qDebug() << "Yes was *not* clicked";
    }


}

/*
 * 名称:generateRangeIP
 * 功能:获取IP地址Range
 * 参数:ip1, ip2
 * 返回:QStringList
 */
QStringList MainWindow::generateRangeIP(QString ip1, QString ip2) {
    QStringList ip1List = ip1.split(".");
    QStringList ip2List = ip2.split(".");
//    if(ip1List.length() != 4 || ip2List.length() != 4){
//        return NULL;
//    }

   // #TODO

}

/*
 * 名称:get_localmachine_ip
 * 功能:获取本机的IP地址
 * 参数:no
 * 返回:QString
 */
QString MainWindow::get_localmachine_ip()
{
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    return ipAddress;
}


MainWindow::~MainWindow()
{
    delete loadingImage;
    delete ui;

}

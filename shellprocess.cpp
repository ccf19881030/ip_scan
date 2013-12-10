#include "shellprocess.h"
#include <QtCore>

ShellProcess::ShellProcess(QObject *parent): QThread(parent){
}

//ShellProcess::~ShellProcess(){
//}

QStringList ShellProcess::getIpRange() {
    return this->ipRange;
}

void ShellProcess::setIpRange(QStringList ipRange) {
    this->ipRange = ipRange;
}

void ShellProcess::run()
    {
//    QStringList test;
//    test << "1" << "22" << "33";
//    QString first;
//    first = test[1];
  //  qDebug() << first;
        QString ip;
        foreach( ip, ipRange ){
            qDebug() << "ping " + ip;
            int exitCode = QProcess::execute("ping", QStringList() << "-c 1" << "-t 2" << ip);
            if (0 == exitCode) {
                // it's alive
                qDebug() << "shell ping " + ip + " sucess";
                emit pingSuccess(ip);
            } else {
                qDebug() << "shell ping " + ip + " failed";
                emit pingFailed(ip);
            }
        }

//    sleep(3);
//    emit pingSuccess("10.0.3.1");
//    sleep(2);
//    emit pingSuccess("10.0.3.2");
    //sleep(10);
        emit pingCompleted();
    }


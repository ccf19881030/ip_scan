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
        //emit pingCompleted();
    }


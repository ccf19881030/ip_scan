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

void ShellProcess::run() {
//    QStringList sshArguments;
//    sshArguments << "-o" << "PasswordAuthentication=no" << "-o" << "ChallengeResponseAuthentication=no" << "-o" << "ConnectTimeout=2";
//    sshArguments << "-o" << "UserKnownHostsFile=/dev/null" << "-o" << "StrictHostKeyChecking=no" << "root@10.0.3.228" << "-i" << "/Users/qichunren/RubymineProjects/luna_scanner/lib/keys/yu_pri";
//    sshArguments << " touch /tmp/qichunren_qqqqqq";

//    int shellExitCode = QProcess::execute("ssh", sshArguments);
//    return;


        QString ip;
        foreach( ip, ipRange ){
            qDebug() << "ping " + ip;
            int exitCode;
       #ifdef Q_OS_WIN
            //启动一个ping进程，然后等待该进程结束。
//              exitCode = QProcess::execute("ping", QStringList() << ip << "-n 1" << "-i 2");
            QString strArg = "ping " + ip + " -n 1 -i 2";
            exitCode = QProcess::execute(strArg);
       #else
            exitCode = QProcess::execute("ping", QStringList() << "-c 1" << "-t 2" << ip);
       #endif

            if (0 == exitCode) {
                // it's alive
                qDebug() << "shell ping " + ip + " success";
                emit commandSuccess(ip);
            } else {
                qDebug() << "shell ping " + ip + " failed";
                emit commandFailed(ip);
            }
        }
}


#ifndef SHELLPROCESS_H
#define SHELLPROCESS_H

#include <QTCore/QStringList>

#include <QThread>

class ShellProcess : public QThread
{

    Q_OBJECT

public:
    explicit ShellProcess(QObject *parent = 0);    

    QStringList getIpRange();

protected:
    void run();


public slots:
    void setIpRange(QStringList ipRange);

signals:
   void commandSuccess(QString ip);
   void commandFailed(QString ip);

public:
     QStringList ipRange;
};

#endif // SHELLPROCESS_H

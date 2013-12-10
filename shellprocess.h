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
   void pingSuccess(QString ip);
   void pingFailed(QString ip);
   void pingCompleted();

public:
     QStringList ipRange;
};

#endif // SHELLPROCESS_H

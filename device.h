#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

class Device : public QObject
{
    Q_OBJECT
public:
    explicit Device(QObject *parent = 0);
    void setIp(QString ip);
    void setSn(QString sn);
    void setModel(QString model);
    void setVersion(QString version);

    QString ip();
    QString sn();
    QString model();
    QString version();

signals:

public slots:

private:
    QString _ip;
    QString _sn;
    QString _model;
    QString _version;

};

#endif // DEVICE_H

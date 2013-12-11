#ifndef SCAN_H
#define SCAN_H

#include <QThread>

class Scan : public QThread
{
    Q_OBJECT
public:
    explicit Scan(QObject *parent = 0);

signals:

protected:
    void run();

public slots:

};

#endif // SCAN_H

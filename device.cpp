#include "device.h"

Device::Device(QObject *parent) : QObject(parent) {
}

QString Device::ip() {
    return _ip;
}

QString Device::sn() {
    return _sn;
}

QString Device::model() {
    return _model;
}

QString Device::version() {
    return _version;
}

void Device::setIp(QString ip) {
    _ip = ip;
}

void Device::setSn(QString sn) {
    _sn = sn;
}

void Device::setModel(QString model) {
    _model = model;
}

void Device::setVersion(QString version) {
    _version = version;
}

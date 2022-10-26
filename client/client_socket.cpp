#include "client_socket.h"

#define NAME_SERVER "/home/vboxuser/Public/server_socket.server"

ClientSocket::ClientSocket(QObject *parent):
socket(new QLocalSocket(parent)){
    connect(socket, &QLocalSocket::errorOccurred, this, &ClientSocket::errorOccurred);
    connect(socket, &QLocalSocket::connected, this, &ClientSocket::connected);
}

void ClientSocket::connected() {
    emit logToBrowser("Connected to Server");

    writeData();
    QString result = readData();
    emit logToBrowser(result);

    disconnectFromServer();
}

ClientSocket::~ClientSocket() {
    delete socket;
}

void ClientSocket::connectToServer() {
    socket->setServerName(NAME_SERVER);
    socket->connectToServer();
}

void ClientSocket::setData(QString& data) {
    data_str = data;
}

void ClientSocket::writeData() {
    if(data_str.length() == 0) {
        return;
    }

    QByteArray buf = data_str.toUtf8();
    socket->write(buf);
}

QString ClientSocket::readData() {
    if(socket->waitForReadyRead()) {
        return socket->readAll();
    }

    return "";
}

void ClientSocket::disconnectFromServer() {
    socket->disconnectFromServer();
}

void ClientSocket::errorOccurred(QLocalSocket::LocalSocketError error) {
    QString str = "Some Error";
    switch(error) {
        case QLocalSocket::ServerNotFoundError:
        str="Server Not Found"; break;
    case QLocalSocket::PeerClosedError:
        str="Server closed Socket"; break;
    }

    emit logToBrowser(str);
}

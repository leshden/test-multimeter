#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <QtCore>
#include <QObject>
#include <QLocalSocket>

class ClientSocket: public QObject {
    Q_OBJECT

public:
    ClientSocket(QObject *parent = nullptr);
    ~ClientSocket();

    void connectToServer();
    void setData(QString& data);

signals:
    void logToBrowser(const QString& text);

private slots:
    void connected();

private:
    void errorOccurred(QLocalSocket::LocalSocketError error);
    void disconnectFromServer();

    void writeData();
    QString readData();

protected:
    QString data_str = "";
    QString error_str = "";
    QLocalSocket* socket = nullptr;

};

#endif // CLIENT_SOCKET_H

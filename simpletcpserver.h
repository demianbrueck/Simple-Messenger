#ifndef CSIMPLETCPSERVER_H
#define CSIMPLETCPSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>
#include <iostream>
#include <QThread>
#include <unistd.h>
#include <QtNetwork>
#include <QQueue>

class CSimpleTcpServer : public QThread
{
    Q_OBJECT
public:
    explicit CSimpleTcpServer(QObject *parent = nullptr);

    void run() override;

    Q_INVOKABLE void writeMessage(QString sMessage);

signals:
    void sigNewMessage(QString message);

public slots:
    void slotNewConnection();
private:
    QTcpServer *m_pTcpServer;
    QTcpSocket *m_pTcpSocket;
    QString m_sMessage;
    QQueue<QByteArray> m_msgQueue;
    int test;
};

#endif // CSIMPLETCPSERVER_H

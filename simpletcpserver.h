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

class CSimpleTcpServer : public QThread
{
    Q_OBJECT
public:
    explicit CSimpleTcpServer(QObject *parent = nullptr);

    void run() override;
signals:

public slots:
    void slotNewConnection();
private:
    QTcpServer *m_pTcpServer;
    QTcpSocket *m_pTcpSocket;
};

#endif // CSIMPLETCPSERVER_H

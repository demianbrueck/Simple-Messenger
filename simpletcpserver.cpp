#include "simpletcpserver.h"

CSimpleTcpServer::CSimpleTcpServer(QObject *parent) : QThread(parent)
{
    m_pTcpSocket = NULL;
    m_pTcpServer = new QTcpServer(this);
    connect(m_pTcpServer,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
    if(m_pTcpServer->listen(QHostAddress("localhost"),6906) == true){
        std::cout << "succesfully listening...\n";
    }
    start();
}

void CSimpleTcpServer::run()
{
    while (true) {
        if(m_pTcpSocket){
            QByteArray data;
            data = m_pTcpSocket->read(1000);
            std::cout << data.toStdString();
        }
        msleep(50);
    }
}

void CSimpleTcpServer::slotNewConnection()
{
    std::cout << "new connection\n";
    m_pTcpSocket = m_pTcpServer->nextPendingConnection();
    m_pTcpSocket->write("test");
}


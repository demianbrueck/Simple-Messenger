#include "simpletcpserver.h"


CSimpleTcpServer::CSimpleTcpServer(QObject *parent) : QThread(parent)
{
    m_pTcpSocket = NULL;
    m_pTcpServer = new QTcpServer(this);
    connect(m_pTcpServer,SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
    if(m_pTcpServer->listen(QHostAddress("localhost"),6906) == true){
        qDebug() << "sucessfully listening";
    }
    start();
}

void CSimpleTcpServer::run()
{
    while (true) {
        if(m_pTcpSocket){
            QByteArray data;
            data = m_pTcpSocket->readAll();
            if(data.toStdString() != ""){
                emit sigNewMessage(QString::fromStdString(data.toStdString()));
                writeMessage("test");
            }
            if(m_msgQueue.count() > 0){
                qDebug() << m_pTcpSocket->write(m_msgQueue.dequeue());
                m_pTcpSocket->flush();
            }
        }
        msleep(500);

        qDebug() << test;

    }
}

void CSimpleTcpServer::writeMessage(QString sMessage)
{
    qDebug() << sMessage.toUtf8();
    m_msgQueue.enqueue(sMessage.toUtf8());

}

void CSimpleTcpServer::slotNewConnection()
{
    qDebug() << "new connection\n";
    m_pTcpSocket = m_pTcpServer->nextPendingConnection();
    qDebug() << m_pTcpSocket->localAddress();
}


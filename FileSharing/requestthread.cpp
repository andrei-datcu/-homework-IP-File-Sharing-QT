#include "requestthread.h"
#include "utils.h"
#include <windows.h>


#include <QTcpSocket>

RequestThread::RequestThread(QObject *parent, int socketDescriptor, ShareFileSystem &share)
	: QThread(parent), 
	socketDescriptor(socketDescriptor),
	share(share)
{
}

RequestThread::~RequestThread()
{
}

void RequestThread::run()
{
	char buffer[1024];
	int size;
	QTcpSocket peer;
	peer.setSocketDescriptor(socketDescriptor);
	peer.setSocketOption(QAbstractSocket::KeepAliveOption, 1);

	if (!peer.waitForReadyRead(6000))
            qDebug("Failed to receive message from client") ;
        else
            qDebug("Read from client");
	
	peer.read(buffer, peer.bytesAvailable());
	size = sizeof(share.toByteArray());
	qDebug()<<buffer << size;
	peer.write((char *)&size, sizeof(int));
	peer.write(share.toByteArray());
	peer.waitForDisconnected(3000);
}

void RequestThread::startRead()
{

}
#include "requestthread.h"
#include "utils.h"
#include <windows.h>
#include "util_serializer.h"


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
	
	readFromSocket(&peer, buffer, MAGICNUMBER);
	size = share.toByteArray().count();
	qDebug()<<buffer << size;
	writeToSocket(&peer, (char*)&size, sizeof(int)); 
	writeToSocket(&peer, share.toByteArray().data(), size); 

	peer.waitForDisconnected(3000);
}

void RequestThread::startRead()
{

}
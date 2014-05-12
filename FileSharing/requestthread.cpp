#include "requestthread.h"
#include "utils.h"
#include <windows.h>


#include <QTcpSocket>

RequestThread::RequestThread(QObject *parent, int socketDescriptor)
	: QThread(parent), socketDescriptor(socketDescriptor)
{
}

RequestThread::~RequestThread()
{
}

void RequestThread::run()
{
	char buffer[1024];
	QTcpSocket peer;
	peer.setSocketDescriptor(socketDescriptor);
	peer.setSocketOption(QAbstractSocket::KeepAliveOption, 1);

	if (!peer.waitForReadyRead(6000))
            qDebug("Failed to receive message from client") ;
        else
            qDebug("Read from client");
	
	peer.read(buffer, peer.bytesAvailable());
	qDebug()<<buffer;
	peer.write("sdasdasdas");
	peer.waitForDisconnected(3000);
}

void RequestThread::startRead()
{

}
#include "fileresolvserver.h"
#include "requestthread.h"

FileResolvServer::FileResolvServer(QObject *parent)
	: QTcpServer(parent)
{
	connectedClients = 0;
}

FileResolvServer::~FileResolvServer()
{

}

void FileResolvServer::incomingConnection(qintptr socketDescriptor)
{
	RequestThread *thread = new RequestThread(this, socketDescriptor);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

	++connectedClients;
	thread->start();
}
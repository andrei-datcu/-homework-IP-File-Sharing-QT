#include "fileresolvserver.h"
#include "requestthread.h"

FileResolvServer::FileResolvServer(QObject *parent, ShareFileSystem &share)
	: QTcpServer(parent),
	share(share)
{
	connectedClients = 0;
}

FileResolvServer::~FileResolvServer()
{

}

void FileResolvServer::incomingConnection(qintptr socketDescriptor)
{
	RequestThread *thread = new RequestThread(this, socketDescriptor, share);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

	++connectedClients;
	thread->start();
}
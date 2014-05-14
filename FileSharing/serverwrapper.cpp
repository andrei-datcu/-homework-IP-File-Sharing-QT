#include "serverwrapper.h"
#include "ServerConnectionThread.h"

ServerWrapper::ServerWrapper(QObject *parent)
	: QTcpServer(parent),
	server(parent)
{

}

ServerWrapper::ServerWrapper(QObject *parent, QMutex *lock)
	: QTcpServer(parent),
	server(parent),
	lock(lock)
{

}

ServerWrapper::~ServerWrapper()
{

}

void ServerWrapper::incomingConnection(qintptr socketDescriptor)
{
	ServerConnectionThread *thread = new ServerConnectionThread(this, socketDescriptor, server, lock);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	((Server*)server)->connectedClients++;
	thread->start();
}

#include "serverwrapper.h"
#include "ServerConnectionThread.h"

ServerWrapper::ServerWrapper(QObject *parent)
	: QTcpServer(parent),
	server(parent)
{
	connectedClients = 0;
}

ServerWrapper::~ServerWrapper()
{

}

void ServerWrapper::incomingConnection(qintptr socketDescriptor)
{
	ServerConnectionThread *thread = new ServerConnectionThread(this, socketDescriptor, server);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connectedClients++;
	thread->start();
}

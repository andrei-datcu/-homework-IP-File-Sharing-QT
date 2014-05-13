#include "server.h"
#include "ServerConnectionThread.h"

Server::Server(QObject *parent)
	: QTcpServer(parent)
{
	connectedClients = 0;
}


Server::~Server()
{

}

void Server::incomingConnection(qintptr socketDescriptor)
{
	ServerConnectionThread *thread = new ServerConnectionThread(this, socketDescriptor);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connectedClients++;
	qDebug("new thread...");
	thread->start();
}
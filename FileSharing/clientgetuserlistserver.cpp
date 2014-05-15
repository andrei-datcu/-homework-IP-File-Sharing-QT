#include "clientgetuserlistserver.h"
#include "clientgetuserlistthread.h"

ClientGetUserListServer::ClientGetUserListServer(QObject *parent)
	: QTcpServer(parent),
	user(parent)
{

}

ClientGetUserListServer::~ClientGetUserListServer()
{

}

void ClientGetUserListServer::incomingConnection(qintptr socketDescriptor)
{
	ClientGetUserListThread *thread = new ClientGetUserListThread(this, socketDescriptor, user);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}

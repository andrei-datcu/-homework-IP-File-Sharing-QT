#include "server.h"
#include "ServerConnectionThread.h"

Server::Server(QObject *parent)
	: QObject(parent)
{
	connectedClients = 0;
	connectServer = new ServerWrapper(this);

}

void Server::startListeningConnectServer()
{
	if (!connectServer->listen(QHostAddress::Any, SERVERPORT))
	{
		qDebug()<<"Adevaratul server nu asculta";
	}
	else
		qDebug()<<"Adevaratul server asculta\n";
}


Server::~Server()
{

}

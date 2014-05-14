#include "server.h"

Server::Server(QObject *parent)
	: QObject(parent)
{
	connectedClients = 0;
	connectServer = new ServerWrapper(this);
	disconnectServer = new ServerDisconnectWrapper(this); 

}

void Server::startListeningConnectServer()
{
	if (!connectServer->listen(QHostAddress::Any, SERVERPORT))
		qDebug()<<"Adevaratul server nu asculta";
	else
		qDebug()<<"Adevaratul server asculta\n";
}


void Server::startListeningDisconnectServer()
{
	if (!disconnectServer->listen(QHostAddress::Any, SERVERPORT + 1))
		qDebug()<<"Adevaratul server nu asculta";
	else
		qDebug()<<"Adevaratul server asculta\n";
}


Server::~Server()
{

}

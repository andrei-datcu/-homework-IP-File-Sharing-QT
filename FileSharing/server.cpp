#include "server.h"

Server::Server(QObject *parent)
	: QObject(parent)
{
	connectedClients = 0;
	lock = new QMutex();
	connectServer = new ServerWrapper(this, lock);
	discServer = new ServerDisconnectWrapper(this, lock);
}

void Server::startListeningConnectServer()
{
	if (!connectServer->listen(QHostAddress::Any, SERVERPORT))
		qDebug()<<"[SERVER] Adevaratul server nu asculta";
	else
		qDebug()<<"[SERVER] Adevaratul server asculta incomingConnections";
}

void Server::startListeningDisconnectServer()
{
	if (!discServer->listen(QHostAddress::Any, SERVERPORT + 1))
		qDebug()<<"[SERVER] Adevaratul server nu asculta";
	else
		qDebug()<<"[SERVER] Adevaratul server asculta disconnectRequests";
}

Server::~Server()
{

}

#include "server.h"

Server::Server(QObject *parent)
	: QObject(parent)
{

	connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
	if (!server.listen(QHostAddress::Any, 8888))
	{
		qDebug()<<"Asd";

	}else qDebug() <<"Ascult!!!\n";
}

void Server::acceptConnection()
{
	client = server.nextPendingConnection();
	connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));
	qDebug()<<"Asd";
}

void Server::startRead()
{
	char buffer[1024] = {0};
	client->read(buffer, client->bytesAvailable());
	qDebug()<<"Received " << endl << buffer<< endl << "disconnected...";
	client->close();
	
}

Server::~Server()
{
	server.close();
}

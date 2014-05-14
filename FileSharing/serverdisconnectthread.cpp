#include "serverdisconnectthread.h"

ServerDisconnectThread::ServerDisconnectThread(QObject *parent)
	: QThread(parent)
{

}

ServerDisconnectThread::ServerDisconnectThread(QObject *parent, int socketDescriptor, QObject *server, QMutex *lock)
	: QThread(parent), 
	server(server),
	socketDescriptor(socketDescriptor),
	lock(lock)
{

}

ServerDisconnectThread::~ServerDisconnectThread()
{

}

void ServerDisconnectThread::run()
{
	connectRequest new_client;
	serverConnectResponse new_response;
	char buffer[10000];

	Server *srv = (Server*) server;

	QTcpSocket peer;
	peer.setSocketDescriptor(socketDescriptor);
	peer.setSocketOption(QAbstractSocket::KeepAliveOption, 1);
	connect(&peer, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
	
	if (!peer.waitForReadyRead(6000))
        qDebug("Failed to receive message with username from client") ;
    else
        qDebug("Reading username from client");

	peer.read(buffer, sizeof(connectRequest));
	memcpy(&new_client, buffer, sizeof(connectRequest));

	srv->userList.remove(new_client.userName);
	((Server*)server)->connectedClients--;

	new_response.valid = 1;
	memcpy(buffer, &new_response, sizeof(serverConnectResponse));
	peer.write(buffer, sizeof(serverConnectResponse));

	qDebug()<< "Ta da" << new_response.size<<srv->userList;
	peer.waitForReadyRead(3000);

}

void ServerDisconnectThread::bytesWritten(qint64 bytes)
{
	qDebug() << bytes << " bytes written...";
}
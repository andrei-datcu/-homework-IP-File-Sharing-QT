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
	//connect(&peer, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
	
	if (!peer.waitForReadyRead(6000))
        qDebug("[SERVER] Failed to receive message with username from client") ;
    else
        qDebug("[SERVER] Reading username from client");

	peer.read(buffer, sizeof(connectRequest));
	memcpy(&new_client, buffer, sizeof(connectRequest));

	qDebug() << "[SERVER] User " << new_client.userName << " wants to disconnect!";

	if (srv->userList.contains(new_client.userName)) {
		lock->lock();
		srv->userList.remove(new_client.userName);
		((Server*)server)->connectedClients--;
		lock->unlock();

		new_response.valid = 1;
		memcpy(buffer, &new_response, sizeof(serverConnectResponse));
		peer.write(buffer, sizeof(serverConnectResponse));

		qDebug() << "[SERVER] User disconnected! " << new_response.size<<srv->userList;
	} else {
		new_response.valid = 0;
		memcpy(buffer, &new_response, sizeof(serverConnectResponse));
		peer.write(buffer, sizeof(serverConnectResponse));
		
		qDebug() << "[SERVER] User is not even connected!";
	}

	peer.waitForReadyRead(3000);

}

void ServerDisconnectThread::bytesWritten(qint64 bytes)
{
	qDebug() << bytes << " bytes written...";
}
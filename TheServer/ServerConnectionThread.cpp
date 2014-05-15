#include "ServerConnectionThread.h"
#include "util_serializer.h"

ServerConnectionThread::ServerConnectionThread(QObject *parent, int socketDescriptor, QObject *server, QMutex *lock)
	: QThread(parent), 
	server(server),
	socketDescriptor(socketDescriptor),
	lock(lock)
{

}

ServerConnectionThread::~ServerConnectionThread()
{

}

void ServerConnectionThread::run()
{
	connectRequest new_client;
	serverConnectResponse new_response;
	char buffer[10000];
	int size;

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
	
	//TODO: Lock pe chestia asta si verificare daca user-ul e la noi
	if (!srv->userList.contains(new_client.userName)) {
		lock->lock();
		srv->userList.insert(new_client.userName, peer.peerAddress().toString());
		lock->unlock();

		qDebug() << "[SERVER] S-a conectat: " << new_client.userName;
		
		QByteArray transfer = toByteArray(srv->userList);
		size = transfer.count();

		peer.write((char *)&size, sizeof(int));
		peer.write(transfer);

		ServerUserlistUpdateThread *thread = new ServerUserlistUpdateThread(0, srv->userList, new_client.userName);
		thread->start();

	} else {
		qDebug() << "[SERVER] Username-ul este deja folosit!";
		new_response.valid = 0;
		memcpy(buffer, &new_response, sizeof(serverConnectResponse));
		peer.write(buffer, sizeof(serverConnectResponse));
	}

	peer.waitForReadyRead(3000);

}

void ServerConnectionThread::bytesWritten(qint64 bytes)
{
	qDebug() << bytes << " bytes written...";
}
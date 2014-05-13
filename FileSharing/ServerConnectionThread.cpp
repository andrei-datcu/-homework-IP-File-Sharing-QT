#include "ServerConnectionThread.h"

ServerConnectionThread::ServerConnectionThread(QObject *parent, int socketDescriptor)
	: QThread(parent), 
	parent(parent),
	socketDescriptor(socketDescriptor)
{

}

ServerConnectionThread::~ServerConnectionThread()
{

}

void ServerConnectionThread::run()
{
	Username nextClient;
	UsernameResponse rsp;
	char buffer[10000];

	Server *srv = (Server*) parent;

	QTcpSocket peer;
	peer.setSocketDescriptor(socketDescriptor);
	peer.setSocketOption(QAbstractSocket::KeepAliveOption, 1);

	if (!peer.waitForReadyRead(6000))
        qDebug("Failed to receive message with username from client") ;
    else
        qDebug("Reading username from client");

	peer.read(buffer, sizeof(Username));
	memcpy(&nextClient, buffer, sizeof(Username));

	qDebug() << "userName: " << QString(nextClient.userName);
	qDebug() << "ipAddress: " << QString(nextClient.ipAddress);

	if (srv->userList.contains(QString(nextClient.userName))) {
		qDebug("Username already used!");
		
		rsp.valid = 0;
		memcpy(buffer, &rsp, sizeof(UsernameResponse));
		peer.write(buffer, sizeof(UsernameResponse));
	} else {
		srv->userList.insert(QString(nextClient.userName), QString(nextClient.ipAddress));
		qDebug() << "User " << nextClient.userName << " connected!";
		
		rsp.valid = 1;
		memcpy(rsp.payload, &srv->userList, sizeof(srv->userList));
		rsp.size = sizeof(srv->userList);
		qDebug() << rsp.valid << " " << rsp.size;
		memcpy(buffer, &rsp, sizeof(UsernameResponse));
		peer.write(buffer, sizeof(UsernameResponse));
	}

}
#include "clientconnectserverthread.h"
#include "user.h"
#include "util_serializer.h"
#include <qmap.h>
#include <QByteArray>

#include <QMap>



ClientConnectServerThread::ClientConnectServerThread(QObject *parent, QString ipAddress, int portNumber, QString username, QObject *user)
	: QThread(parent),
	ipAddress(ipAddress),
	portNumber(portNumber),
	username(username),
	user(user)
{

}

ClientConnectServerThread::~ClientConnectServerThread()
{

}

void ClientConnectServerThread::run()
{
	peer = new QTcpSocket();
	doConnect();
	loginToServer();
	peer->waitForReadyRead(5000);
	getUserList();
}

void ClientConnectServerThread::doConnect()
{
	qDebug() << "[CLIENT] Connecting...";

	peer->connectToHost(ipAddress, portNumber);
	if (!peer->waitForConnected(5000))
		qDebug()<<"[CLIENT] Error at Connecting...";

}

void ClientConnectServerThread::loginToServer()
{
	char buffer[2000];
	connectRequest new_client;
	strncpy(new_client.userName, username.toLatin1(), strlen(username.toLatin1()));
	qDebug() << "[CLIENT] " << new_client.userName << " is trying to log in!";
	memcpy(buffer, &new_client, sizeof(connectRequest));
	writeToSocket(peer, buffer, sizeof(connectRequest));
	//peer->write(buffer, sizeof(connectRequest));
}

void ClientConnectServerThread::getUserList()
{
	char buffer[4000];
	QMap<QString, QString> userList;
	serverConnectResponse new_response;
	int size, copyOfSize;
	User *the_user = (User *) user;

	readFromSocket(peer, buffer, sizeof(int));
	memcpy(&size, buffer, sizeof(int));
	if (size != 0)
	{
		qDebug() << "Clientttt" << size;
		copyOfSize = size;
		readFromSocket(peer, buffer, size);

		QByteArray data(buffer, copyOfSize);
		userList = fromByteArray(data);
		qDebug() << "Clientttt" << userList;
		
		the_user->userList = userList; 
		the_user->usernameOk = true;
		emit gotUserList();
	}
	else
	{
		the_user->usernameOk = false;
	}
}
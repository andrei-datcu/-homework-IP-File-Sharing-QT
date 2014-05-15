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
	peer->write(buffer, sizeof(connectRequest));
}

void ClientConnectServerThread::getUserList()
{
	char buffer[4000];
	QByteArray data, buff;
	QMap<QString, QString> userList;
	serverConnectResponse new_response;
	int size;
	User *the_user = (User *) user;

	peer->read(buffer, sizeof(int));
	memcpy(&size, buffer, sizeof(int));
	if (size != 0)
	{
		qDebug() << "Clientttt" << size;
		while (size > 0)
		{
			buff = peer->readAll();
			data += buff;
			size -= buff.size();
		}
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
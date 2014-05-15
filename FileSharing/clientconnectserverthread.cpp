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

	//connect(peer, SIGNAL(connected()), this, SLOT(connected()));
	//connect(peer, SIGNAL(disconnected()), this, SLOT(disconnected()));
	//connect(peer, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
	//connect(peer, SIGNAL(readyRead()), this, SLOT(readyRead()));

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
		
		User *the_user = (User *) user;
		the_user->userList = userList; 
		emit gotUserList();
	}
	else
		emit changeUsername();

}

void ClientConnectServerThread::disconnected()
{
	qDebug() << "disconnected...";
}

void ClientConnectServerThread::connected()
{
	qDebug() << "Client connected...";

}

void ClientConnectServerThread::bytesWritten(qint64 bytes)
{
	qDebug() << bytes << " bytes written...";
}

void ClientConnectServerThread::readyRead()
{
	char buffer[5000];
	peer->read(buffer, peer->bytesAvailable());
	qDebug() << "Client" << buffer;
}
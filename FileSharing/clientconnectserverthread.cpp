#include "clientconnectserverthread.h"

ClientConnectServerThread::ClientConnectServerThread(QObject *parent, QString ipAddress, int portNumber, QString username)
	: QThread(parent),
	ipAddress(ipAddress),
	portNumber(portNumber),
	username(username)
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
	QMap<QString, QString> userList;
	serverConnectResponse new_response;

	peer->read(buffer, sizeof(serverConnectResponse));
	memcpy(&new_response, buffer, sizeof(serverConnectResponse));
	memcpy(&userList, new_response.payload, new_response.size);
	qDebug() << "[CLIENT] Got userList: "<<new_response.size << new_response.valid << userList;
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
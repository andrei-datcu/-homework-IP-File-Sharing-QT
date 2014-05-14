#include "clientdisconnectserverthread.h"

ClientDisconnectServerThread::ClientDisconnectServerThread(QObject *parent, QString ipAddress, int portNumber, QString username)
	: QThread(parent),
	ipAddress(ipAddress),
	portNumber(portNumber),
	username(username)
{

}

ClientDisconnectServerThread::~ClientDisconnectServerThread()
{

}


void ClientDisconnectServerThread::run()
{
	peer = new QTcpSocket();

	qDebug() << "[CLIENT] Connecting to DisconnectSocket...";

	peer->connectToHost(ipAddress, portNumber);

	if (!peer->waitForConnected(5000))
		qDebug()<<"[CLIENT] Error at Connecting...";

	char buffer[2000];
	connectRequest new_client;
	strncpy(new_client.userName, username.toLatin1(), strlen(username.toLatin1()));

	qDebug() << "[CLIENT] My name is " << new_client.userName << " and i want to disconnect from server!";
	memcpy(buffer, &new_client, sizeof(connectRequest));
	peer->write(buffer, sizeof(connectRequest));

	peer->waitForReadyRead(5000);

	serverConnectResponse new_response;
	peer->read(buffer, sizeof(serverConnectResponse));

	memcpy(&new_response, buffer, sizeof(serverConnectResponse));
	if (new_response.valid == 1)
		qDebug("[CLIENT] Successfully disconnected!");
	else
		qDebug("[CLIENT] Did not disconnect!");
}

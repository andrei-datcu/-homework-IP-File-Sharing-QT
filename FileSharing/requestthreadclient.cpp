#include "requestthreadclient.h"


RequestThreadClient::RequestThreadClient(QObject *parent)
	:QThread(parent)
{

}


RequestThreadClient::~RequestThreadClient(void)
{
	//free(peer);
}

void RequestThreadClient::run()
{
	peer = new QTcpSocket();
	doConnect();
	makeRequest();
	peer->waitForReadyRead(5000);
}


void RequestThreadClient::makeRequest()
{
	peer->write("Taygun biatch", 20);
}

void RequestThreadClient::doConnect()
{
	qDebug() << "Connecting...";

	connect(peer, SIGNAL(connected()), this, SLOT(connected()));
	connect(peer, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(peer, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
	connect(peer, SIGNAL(readyRead()), this, SLOT(readyRead()));

	peer->connectToHost("127.0.0.1", 8888);
	if (!peer->waitForConnected(5000))
		qDebug()<<"Error at Connecting...";

}

void RequestThreadClient::readyRead()
{
	char buffer[1000];
	peer->read(buffer, peer->bytesAvailable());
	qDebug() << "Client" << buffer;
}

void RequestThreadClient::disconnected()
{
	qDebug() << "disconnected...";
}

void RequestThreadClient::connected()
{
	qDebug() << "Client connected...";

}

void RequestThreadClient::bytesWritten(qint64 bytes)
{
	qDebug() << bytes << " bytes written...";
}

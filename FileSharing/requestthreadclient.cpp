#include "requestthreadclient.h"


RequestThreadClient::RequestThreadClient(QObject *parent)
	:QThread(parent),
	share(NULL)
{
}

RequestThreadClient::RequestThreadClient(QObject *parent, QString ipAddress, int portNumber, int type, ShareFileSystem **share)
	:QThread(parent),
	ipAddress(ipAddress),
	portNumber(portNumber),
	type(type),
	share(share)
{

}



RequestThreadClient::~RequestThreadClient(void)
{
}

void RequestThreadClient::run()
{
	peer = new QTcpSocket();
	doConnect();
	switch(type)
	{
	case 0:
		getFileList();
		break;
	
	case 1:
		break;
	default:
		break;
	}
	//makeRequest();
	peer->waitForReadyRead(5000);
}


void RequestThreadClient::makeRequest()
{
	peer->write("Taygun biatch", 20);
}

void RequestThreadClient::getFileList()
{
	QString buffer("Filelist");
	peer->write("Filelist", 8);
}

void RequestThreadClient::doConnect()
{
	qDebug() << "Connecting...";

	connect(peer, SIGNAL(connected()), this, SLOT(connected()));
	connect(peer, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(peer, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
	connect(peer, SIGNAL(readyRead()), this, SLOT(readyRead()));

	peer->connectToHost(ipAddress, portNumber);
	if (!peer->waitForConnected(5000))
		qDebug()<<"Error at Connecting...";

}

void RequestThreadClient::readyRead()
{
	char buffer[5000];
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

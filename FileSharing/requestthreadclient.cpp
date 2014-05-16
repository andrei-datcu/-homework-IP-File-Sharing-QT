#include "requestthreadclient.h"
#include "util_serializer.h"


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
	getFileList();
	peer->waitForReadyRead(5000);
}

void RequestThreadClient::getFileList()
{
	QByteArray filelist("filelist");
	int sizeToWrite = filelist.count();
	int written = 0;
	while (sizeToWrite > 0)
	{
		written = peer->write(filelist.data() + written);
		sizeToWrite -= written;
	}
}

void RequestThreadClient::doConnect()
{
	qDebug() << "Connecting..." << portNumber;

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
	int size;

	readFromSocket(peer, buffer, sizeof(int));
	memcpy(&size, buffer, sizeof(int));

	readFromSocket(peer, buffer, size);
	QByteArray content(buffer, size);
    *share = new ShareFileSystem(content);
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

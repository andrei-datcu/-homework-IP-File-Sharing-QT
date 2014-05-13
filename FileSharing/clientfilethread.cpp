#include "clientfilethread.h"
#include "utils.h"

ClientFileThread::ClientFileThread(QObject *parent, QString ipAddress, int portNumber, int fileID)
	: QThread(parent),
	ipAddress(ipAddress),
	portNumber(portNumber),
	fileID(fileID)
{

}

ClientFileThread::~ClientFileThread()
{

}

void ClientFileThread::run()
{
	peer = new QTcpSocket();
	doConnect();
	getFile();
	peer->waitForReadyRead(5000);
}


void ClientFileThread::getFile()
{
	char buffer[50];
	fileRequest new_request;
	new_request.fileID=fileID;
	memcpy(buffer, &new_request, sizeof(fileRequest));

	peer->write(buffer, sizeof(fileRequest));
	peer->waitForReadyRead(3000);
}

void ClientFileThread::doConnect()
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

void ClientFileThread::readyRead()
{
	char buffer[5000];
	int fileSize = 0;
	fileRequest new_request;

	peer->read(buffer, sizeof(fileRequest));
	memcpy(&new_request, buffer, sizeof(fileRequest));
	qDebug() << "Client"<<new_request.size << " "  << new_request.payload;
	fileSize = new_request.size;

	//while(fileSize > 0)
	//{
	//
	//}
}

void ClientFileThread::disconnected()
{
	qDebug() << "disconnected...";
}

void ClientFileThread::connected()
{
	qDebug() << "Client connected...";

}

void ClientFileThread::bytesWritten(qint64 bytes)
{
	qDebug() << bytes << " bytes written...";
}

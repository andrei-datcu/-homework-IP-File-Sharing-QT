#include "clientfilethread.h"
#include "utils.h"

#define FAKECHUNKSIZE 5000

#include <QFile>
ClientFileThread::ClientFileThread(QObject *parent, QString ipAddress, int portNumber, int fileID, QString downloadPath)
	: QThread(parent),
	ipAddress(ipAddress),
	portNumber(portNumber),
	fileID(fileID),
	downloadPath(downloadPath)
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
	downloadFile();
}


void ClientFileThread::getFile()
{
	char buffer[50];
	fileRequest new_request;
	new_request.fileID=fileID;
	memcpy(buffer, &new_request, sizeof(fileRequest));

	peer->write(buffer, sizeof(fileRequest));
}

void ClientFileThread::doConnect()
{
	qDebug() << "Connecting...";

	connect(peer, SIGNAL(connected()), this, SLOT(connected()));
	connect(peer, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(peer, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

	peer->connectToHost(ipAddress, portNumber);
	if (!peer->waitForConnected(5000))
		qDebug()<<"Error at Connecting...";
}

void ClientFileThread::downloadFile()
{
	char buffer[9000];
	int fileSize = 0;
	int received = 0;
	int sum_received = 0;
	fileRequest new_request;
	QByteArray data;

	peer->waitForReadyRead(5000);

	peer->read(buffer, sizeof(fileRequest));
	memcpy(&new_request, buffer, sizeof(fileRequest));
	qDebug() << "Client"<<new_request.size << " "  << new_request.payload;
	
	fileSize = new_request.size;
	QFile file(downloadPath);
	file.open(QFile::WriteOnly);
	qDebug()<<fileSize;
	while(fileSize > 0)
	{
    	//data = peer->read(FAKECHUNKSIZE);
        data = peer->readAll();
		received = data.count();
        qDebug () << "Recieved " << received << " bytes\n";
		sum_received += received;
		emit gotBytes(sum_received);
		file.write(data);
		fileSize -= received;
	}

	file.close();
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

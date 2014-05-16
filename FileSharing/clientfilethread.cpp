#include "clientfilethread.h"
#include "utils.h"
#include "util_serializer.h"

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

	writeToSocket(peer, buffer, sizeof(fileRequest));
	//peer->write(buffer, sizeof(fileRequest));
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
    const int bufsize = 10000;
	char buffer[bufsize];
	int fileSize = 0;
	int received = 0;
	int sum_received = 0;
	fileRequest new_request;
	QByteArray data;

	if (!peer->waitForReadyRead(-1)){
        emit connectionFailed("");
    }

	readFromSocket(peer, buffer, sizeof(fileRequest));
	memcpy(&new_request, buffer, sizeof(fileRequest));
	qDebug() << "Client"<<new_request.size << " "  << new_request.payload;
	
	fileSize = new_request.size;
	QFile file(downloadPath);
	file.open(QFile::WriteOnly);
	qDebug()<<fileSize;
	while(fileSize > 0)
	{

        received = peer->read(buffer, bufsize);
        if (received == -1){
            file.close();
            QFile::remove(downloadPath);
            emit connectionFailed(downloadPath);
            return;
        }

        qDebug() << received << "\n";
 
		sum_received += received;
		emit gotBytes(sum_received);
		file.write(buffer, received);
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

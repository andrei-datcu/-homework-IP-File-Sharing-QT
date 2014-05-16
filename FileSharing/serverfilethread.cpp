#include "serverfilethread.h"
#include "utils.h"
#include "util_serializer.h"


ServerFileThread::ServerFileThread(QObject *parent, int socketDescriptor, ShareFileSystem &share)
	: QThread(parent),
	socketDescriptor(socketDescriptor),
	share(share)
{

}

ServerFileThread::~ServerFileThread()
{

}

void ServerFileThread::run()
{
	char buffer[10000];
	fileRequest new_request;
	QByteArray data;

	QTcpSocket peer;
	peer.setSocketDescriptor(socketDescriptor);
	peer.setSocketOption(QAbstractSocket::KeepAliveOption, 1);
	connect(&peer, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

	if (!peer.waitForReadyRead(6000))
            qDebug("Failed to receive message from client") ;
        else
            qDebug("Read from client");
	
	readFromSocket(&peer, buffer,sizeof(fileRequest));
	//peer.read(buffer, sizeof(fileRequest));
	memcpy(&new_request, buffer, sizeof(fileRequest));
	//qDebug()<< "Staaan:"<<new_request.fileID << share.getFileFromId(new_request.fileID);
	//TODO get filepath from ShareFileSystem

	QFile file(share.getFileFromId(new_request.fileID));
	QByteArray filename;
	if (!file.exists())
	{
		qDebug()<<"Nu s-a putut deschide fisierul";
	}

	if (file.open(QFile::ReadOnly)){
		data = file.readAll();
	}
	new_request.size = data.size();
	filename = file.fileName().toLatin1();
	strncpy(new_request.payload, filename.data(), strlen(filename.data()));
	memcpy(buffer, &new_request, sizeof(fileRequest));
	writeToSocket(&peer, buffer, sizeof(fileRequest));


	qDebug()<<"Data: "<<data.size() <<"  " <<new_request.payload;
	const int buffsize = 10000;
    char *buff = data.data();
	for (int c = data.count(); c > 0;){
        int written = peer.write(buff, std::min(buffsize, c));
        if (written == -1)
            break;
        c -= written;
        buff += written;
    }

	peer.disconnectFromHost();
	peer.waitForDisconnected();
}

void ServerFileThread::bytesWritten(qint64 bytes)
{
	qDebug() << bytes << " bytes written...";
}


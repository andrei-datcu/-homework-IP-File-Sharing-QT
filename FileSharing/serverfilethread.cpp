#include "serverfilethread.h"
#include "utils.h"


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
	if (!peer.waitForReadyRead(6000))
            qDebug("Failed to receive message from client") ;
        else
            qDebug("Read from client");
	
	peer.read(buffer, sizeof(fileRequest));
	memcpy(&new_request, buffer, sizeof(fileRequest));
	qDebug()<< "Staaan:"<<new_request.fileID;
	//TODO get filepath from ShareFileSystem

	QFile file("test_send.txt");
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
	memcpy(new_request.payload, filename.data(), sizeof(filename.data()) + 5);
	memcpy(buffer, &new_request, sizeof(fileRequest));
	peer.write(buffer, sizeof(fileRequest));


	qDebug()<<"Data: "<<data.size() <<"  " <<new_request.payload;
	//peer.write(data.size);
	peer.waitForReadyRead(3000);
}


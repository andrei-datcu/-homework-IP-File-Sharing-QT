#include "clientrespondtosearchthread.h"
#include <QTcpSocket>
#include <QMap>
#include "util_serializer.h"
#include "user.h"

ClientRespondToSearchThread::ClientRespondToSearchThread(QObject *parent, int socketDescriptor, QObject *user)
	: QThread(parent),
	user(user),
	socketDescriptor(socketDescriptor)
{

}

ClientRespondToSearchThread::~ClientRespondToSearchThread()
{

}

void ClientRespondToSearchThread::run()
{
	int size;
	char buffer[100];
	QByteArray buff, data;
	QTcpSocket peer;
	QMap<QString, QString> result;

	User *the_user = (User*) user;
	


	peer.setSocketDescriptor(socketDescriptor);
	peer.setSocketOption(QAbstractSocket::KeepAliveOption, 1);

	if (!peer.waitForReadyRead(6000))
            qDebug("Failed to receive message from client") ;
        else
            qDebug("Read from client");


	peer.read(buffer,sizeof(int));
	memcpy(&size, buffer, sizeof(int));

	while(size > 0)
	{
		buff = peer.readAll();
		data += buff;
		size -= buff.size();
	}


	qDebug() << data;
	//qDebug() << the_user->shared->toByteArray();
	auto lista = the_user->shared->searchInFiles(QString(data));
	for (auto item: lista)
	{
		qDebug()<< item.first << item.second;
		result[QString::number(item.first)] = item.second;
	}
	data = toByteArray(result);
	if (result.size() > 0)
	{
		size = sizeof(data);
		peer.write((char*)&size, sizeof(int));
		peer.write(data);
	}
	else
	{
		size = 0;
		peer.write((char*)&size, sizeof(int));
	}
	peer.waitForReadyRead(3000);
}

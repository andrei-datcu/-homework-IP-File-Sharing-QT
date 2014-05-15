#include "clientsearchthread.h"
#include "utils.h"
#include "util_serializer.h"
#include "user.h"
#include <QByteArray>

ClientSearchThread::ClientSearchThread(QObject *parent, QString searchName)
	: QThread(parent),
	searchName(searchName),
	user(parent)
{
	data = searchName.toLatin1();
	size = data.count();
}

ClientSearchThread::~ClientSearchThread()
{

}

void ClientSearchThread::run()
{
	peer = new QTcpSocket();
	User *the_user = (User*) user;
	QMap<QString, QString>::iterator i;
	for (i=the_user->userList.begin(); i!=the_user->userList.end(); ++i)
	{
		doConnect(i.value());
		doTheSearch();
		//peer->disconnectFromHost();
		//peer->waitForDisconnected(10);
	}

	peer->waitForReadyRead(3000);
}

void ClientSearchThread::doConnect(QString ipAddress)
{
	qDebug()<<"Ii cer lui "<<ipAddress << SEARCHPORT;
	peer->connectToHost(ipAddress, SEARCHPORT);
	if (!peer->waitForConnected(5000))
		qDebug()<<"Error at Connecting...";
}

void ClientSearchThread::doTheSearch()
{
	int new_size;
	char buffer[100];
	QByteArray recvData, buff;
	QMap<QString, QString> oneResult;


	peer->write((char *)&size, sizeof(int));
	peer->write(data);

	qDebug()<<"Mircea asteapta";
	peer->waitForReadyRead(-1);
	qDebug()<<"Mircea nu asteapta";

	peer->read(buffer, sizeof(int));
	
	//memcpy(&new_size, buffer, sizeof(int));
	//if (new_size != 0)
	//{
	//	while (new_size > 0)
	//	{
	//		buff = peer->readAll();
	//		data += buff;
	//		size -= buff.size();
	//	}
	//}
	//
	//oneResult = fromByteArray(data);
	//qDebug() << "Mircea" << oneResult;
}

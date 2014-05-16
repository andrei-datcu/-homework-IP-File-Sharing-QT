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
	QTcpSocket peer;
	std::list<std::tuple<int, int, QString>> result;

	User *the_user = (User*) user;
	


	peer.setSocketDescriptor(socketDescriptor);
	peer.setSocketOption(QAbstractSocket::KeepAliveOption, 1);

	if (!peer.waitForReadyRead(6000))
            qDebug("Failed to receive message from client") ;
        else
            qDebug("Read from client");


	readFromSocket(&peer, buffer, sizeof(int));
	memcpy(&size, buffer, sizeof(int));

	readFromSocket(&peer, buffer, size);
	QByteArray data(buffer, size);

	qDebug() << data;
	int tuple_size, tuple_fileID;
	QString tuple_filename;
	auto lista = the_user->shared->searchInFiles(QString(data));
	data = searchResultsToByteArray(lista);
	
	if (lista.size() > 0)
	{
		size = data.count();
		writeToSocket(&peer, (char*)&size, sizeof(int));
		writeToSocket(&peer, data.data(), size);
	}
	else
	{
		size = 0;
		writeToSocket(&peer, (char*)&size, sizeof(int));
	}
	peer.waitForReadyRead(3000);
}

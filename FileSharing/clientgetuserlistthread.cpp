#include "clientgetuserlistthread.h"
#include <QByteArray>
#include "user.h"
#include "util_serializer.h"

ClientGetUserListThread::ClientGetUserListThread(QObject *parent, int socketDescriptor, QObject *user)
	: QThread(parent),
	socketDescriptor(socketDescriptor),
	user(user)
{

}

ClientGetUserListThread::~ClientGetUserListThread()
{

}

void ClientGetUserListThread::run()
{
	QByteArray data, buff;
	QTcpSocket peer;
	QMap<QString, QString> userList;
	char buffer[2000];
	int size;
	peer.setSocketDescriptor(socketDescriptor);
	peer.setSocketOption(QAbstractSocket::KeepAliveOption, 1);

	if (!peer.waitForReadyRead(6000))
            qDebug("Failed to receive message from client") ;
        else
            qDebug("Read from client");
	
	peer.read(buffer, sizeof(int));
	memcpy(&size, buffer, sizeof(int));

	if (size != 0)
	{
		while (size > 0)
		{
			buff = peer.readAll();
			data += buff;
			size -= buff.size();
		}
		userList = fromByteArray(data);
		
	}
	
	User *the_user = (User *)user;
	qDebug() << "[CLIENT] Am primit: " << userList;
	
	the_user->userList = userList;
	emit the_user->gotNewUserList();
	
	
}

#include "clientgetuserlistthread.h"
#include <QByteArray>
#include "user.h"

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
	QByteArray data;
	QTcpSocket peer;
	peer.setSocketDescriptor(socketDescriptor);
	peer.setSocketOption(QAbstractSocket::KeepAliveOption, 1);

	if (!peer.waitForReadyRead(6000))
            qDebug("Failed to receive message from client") ;
        else
            qDebug("Read from client");
	
	data = peer.readAll();
	qDebug()<<data.data();
	User *the_user = (User *)user;
	emit the_user->gotNewUserList();
	
	
}

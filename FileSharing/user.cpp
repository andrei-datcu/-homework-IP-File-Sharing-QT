#include "user.h"
#include "requestthread.h"
#include "requestthreadclient.h"
#include "fileresolvserver.h"
#include "utils.h"
#include <windows.h>

#include <QDebug>



User::User(QString username, QObject *parent)
	: QObject(parent),
	  username(username)
{
	shared = new ShareFileSystem(QString(TESTFILE));
	fileListServer = new FileResolvServer(this, *shared);
	fileServer = new FileServer(this, *shared);
    startListeningFilelist();
    startListeningFile();
}

void User::connectToServer(QString ipAddress, int portNumber)
{
	ClientConnectServerThread *thread = new ClientConnectServerThread(this, ipAddress, portNumber, username);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}

void User::disconnectFromServer(QString ipAddress, int portNumber)
{
	ClientDisconnectServerThread *thread = new ClientDisconnectServerThread(this, ipAddress, portNumber, username);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}

void User::startListeningFilelist()
{
	if (!fileListServer->listen(QHostAddress::Any, FILELISTPORT))
		qDebug() << "Serverul nu asculta";
	else
		qDebug() << "Serverul asculta pe filelistSocket";
}

void User::startListeningFile()
{
	if (!fileServer->listen(QHostAddress::Any, FILEPORT))
		qDebug() << "Serverul nu asculta";
	else
		qDebug() << "Serverul asculta pe fileSocket";
}


User::~User()
{
	shared->saveToFile(TESTFILE);

	fileListServer->close();
	free(in_socket);
	free(out_socket);
	free(shared);
}

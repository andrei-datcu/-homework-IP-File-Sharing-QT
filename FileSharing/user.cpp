#include "user.h"
#include "requestthread.h"
#include "requestthreadclient.h"
#include "clientsearchthread.h"
#include "fileresolvserver.h"
#include "utils.h"
#include <windows.h>

#include <QDebug>



User::User(QString username, QObject *parent)
	: QObject(parent),
	  username(username)
{
	connect(this, SIGNAL(gotNewUserList()), this, SLOT(test_slot()));
	connect(this, SIGNAL(gotSearchResults()), this, SLOT(test_slot()));
	shared = new ShareFileSystem(QString(TESTFILE));
	fileListServer = new FileResolvServer(this, *shared);
	fileServer = new FileServer(this, *shared);
	userListServer = new ClientGetUserListServer(this);
	searchServer = new ClientRespondToSearchServer(this);
    startListeningFilelist();
    startListeningFile();
	startListeningUserList();
	startListeningSearch();
}

ClientConnectServerThread* User::connectToServer(QString ipAddress, int portNumber)
{
	ClientConnectServerThread *thread = new ClientConnectServerThread(this, ipAddress, portNumber, username, this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
    serverIp = ipAddress;
    serverPortNo = portNumber;
	return thread;
}

ClientDisconnectServerThread* User::disconnectFromServer()
{
	ClientDisconnectServerThread *thread = new ClientDisconnectServerThread(this, serverIp, serverPortNo + 1, username);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
    return thread;
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

void User::startListeningUserList()
{
	if (!userListServer->listen(QHostAddress::Any, USERLISTPORTONCLIENT))
		qDebug() << "Serverul nu asculta";
	else
		qDebug() << username << "Serverul asculta pe userListSocket";
}

void User::startListeningSearch()
{
	if (!searchServer->listen(QHostAddress::Any, SEARCHPORT))
		qDebug() << "Serverul de search  nu asculta";
	else
		qDebug() << username << "Serverul de search asculta pe "<<SEARCHPORT;
}



User::~User(){

	shared->saveToFile(TESTFILE);
	fileListServer->close();
	free(shared);
}

void User::test_slot()
{
	qDebug()<<"Merge slotul si semnalul :D" << searchResult.size();
}


ClientSearchThread* User::searchFile(QString searchName)
{
	ClientSearchThread *thread = new ClientSearchThread(this, searchName);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
	return thread;
}
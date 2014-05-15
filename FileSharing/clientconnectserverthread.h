#pragma once

#ifndef CLIENTCONNECTSERVERTHREAD_H
#define CLIENTCONNECTSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "utils.h"

class ClientConnectServerThread : public QThread
{
	Q_OBJECT

public:
	ClientConnectServerThread(QObject *parent, QString ipAddress, int portNumber, QString username, QObject *user);
	~ClientConnectServerThread();

	QString ipAddress;
	int portNumber;

	void run();
	void doConnect();
	void loginToServer();
	void makeRequest();
	void getUserList();


signals:
		void gotUserList();
		void changeUsername();

private:
	int socketDescriptor;
	QTcpSocket *peer;
	QString username;
	QObject *user;
	
};

#endif // CLIENTCONNECTSERVERTHREAD_H

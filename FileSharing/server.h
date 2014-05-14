#ifndef SERVER_H
#define SERVER_H


#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMap>

#include "utils.h"
#include "serverwrapper.h"
#include "ServerConnectionThread.h"
#include "serverdisconnectwrapper.h"
#include "serverdisconnectthread.h"

class Server : public QObject
{
	Q_OBJECT

public:
	Server(QObject *parent = NULL);
	~Server();

	QMap<QString, QString> userList;
	int connectedClients;

	void startListeningConnectServer();
	void startListeningDisconnectServer();

	ServerWrapper *connectServer;
	ServerDisconnectWrapper *disconnectServer;

private:
	

};

#endif // SERVER_H

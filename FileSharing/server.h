#ifndef SERVER_H
#define SERVER_H

#include "serverwrapper.h"

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMap>

class Server : public QObject
{
	Q_OBJECT

public:
	Server(QObject *parent = NULL);
	~Server();
	QMap<QString, QString> userList;

	void startListeningConnectServer();

private:
	int connectedClients;
	ServerWrapper *connectServer;
};

#endif // SERVER_H

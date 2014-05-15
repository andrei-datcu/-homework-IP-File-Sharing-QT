#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMap>
#include <QString>
#include <QMutex>

#include "utils.h"
#include "serverwrapper.h"
#include "serverdisconnectwrapper.h"
#include "serveruserlistupdatethread.h"


class Server : public QObject
{
	Q_OBJECT

public:
	Server(QObject *parent = NULL);
	~Server();

	void startListeningConnectServer();
	void startListeningDisconnectServer();

	QMap<QString, QString> userList;
	int connectedClients;
	QMutex *lock;

private:
	ServerWrapper *connectServer;
	ServerDisconnectWrapper *discServer;
};

#endif // SERVER_H

#ifndef SERVERWRAPPER_H
#define SERVERWRAPPER_H

#include <QTcpServer>
#include <QMap>

class ServerWrapper : public QTcpServer
{
	Q_OBJECT

public:
	ServerWrapper(QObject *parent = NULL);
	~ServerWrapper();
	QMap<QString, QString> userList;

protected:
	void incomingConnection(qintptr socketDescriptor);

private:
	int connectedClients;
	QObject *server;
};

#endif // SERVERWRAPPER_H

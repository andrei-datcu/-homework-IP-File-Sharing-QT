#ifndef CLIENTGETUSERLISTSERVER_H
#define CLIENTGETUSERLISTSERVER_H

#include <QTcpServer>

class ClientGetUserListServer : public QTcpServer
{
	Q_OBJECT

public:
	ClientGetUserListServer(QObject *parent);
	~ClientGetUserListServer();


protected:
	void incomingConnection(qintptr socketDescriptor);

private:
	QObject *user;
};

#endif // CLIENTGETUSERLISTSERVER_H

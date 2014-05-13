#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMap>

class Server : public QTcpServer
{
	Q_OBJECT

public:
	Server(QObject *parent = NULL);
	~Server();
	QMap<QString, QString> userList;

protected:
	void incomingConnection(qintptr socketDescriptor);

private:
	int connectedClients;

};

#endif // SERVER_H

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class Server : public QObject
{
	Q_OBJECT

public:
	Server(QObject *parent = NULL);
	~Server();

	public slots:
		void acceptConnection();
		void startRead();

private:
	QTcpServer server;
	QTcpSocket *client;
	
};

#endif // SERVER_H

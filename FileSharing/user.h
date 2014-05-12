#ifndef USER_H
#define USER_H
#include "fileresolvserver.h"

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class User : public QObject
{
	Q_OBJECT

public:
	User(QString username, QObject *parent = 0);
	QString username;
	QTcpSocket *in_socket, *out_socket;
	void startListening();
	void makeRequest();

	~User();

private:
	FileResolvServer server;
	int numberIn;
	
};

#endif // USER_H

#ifndef USER_H
#define USER_H
#include "fileresolvserver.h"
#include "fileserver.h"
#include "ShareFileSystem.h"

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
	void startListeningFilelist();
	void startListeningFile();

	~User();

private:
	FileResolvServer *fileListServer;
	FileServer *fileServer;
	ShareFileSystem *shared;
	int numberIn;
	
};

#endif // USER_H

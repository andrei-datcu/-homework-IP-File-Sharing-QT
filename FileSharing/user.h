#ifndef USER_H
#define USER_H
#include "fileresolvserver.h"
#include "fileserver.h"
#include "ShareFileSystem.h"
#include "clientconnectserverthread.h"
#include "clientdisconnectserverthread.h"

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
	void connectToServer(QString ipAddress, int portNumber);
	void disconnectFromServer(QString ipAddress, int portNumber);
	~User();

    ShareFileSystem *shared;

private:
	FileResolvServer *fileListServer;
	FileServer *fileServer;
	int numberIn;
	
};

#endif // USER_H

#ifndef FILERESOLVSERVER_H
#define FILERESOLVSERVER_H

#include "ShareFileSystem.h"

#include <QTcpServer>

class FileResolvServer : public QTcpServer
{
	Q_OBJECT

public:
	FileResolvServer(QObject *parent, ShareFileSystem &share);
	~FileResolvServer();


protected:
	void incomingConnection(qintptr socketDescriptor);

private:
	int connectedClients;
	ShareFileSystem &share;

	
};

#endif // FILERESOLVSERVER_H

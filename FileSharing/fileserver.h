#ifndef FILESERVER_H
#define FILESERVER_H

#include "ShareFileSystem.h"

#include <QTcpServer>

class FileServer : public QTcpServer
{
	Q_OBJECT

public:
	FileServer(QObject *parent, ShareFileSystem &share);
	~FileServer();

protected:
	void incomingConnection(qintptr socketDescriptor);

private:
	ShareFileSystem &share;
	
};

#endif // FILESERVER_H

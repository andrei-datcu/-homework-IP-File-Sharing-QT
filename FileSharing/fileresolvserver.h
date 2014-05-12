#ifndef FILERESOLVSERVER_H
#define FILERESOLVSERVER_H

#include <QTcpServer>

class FileResolvServer : public QTcpServer
{
	Q_OBJECT

public:
	FileResolvServer(QObject *parent);
	~FileResolvServer();


protected:
	void incomingConnection(qintptr socketDescriptor);

private:
	int connectedClients;
	
};

#endif // FILERESOLVSERVER_H

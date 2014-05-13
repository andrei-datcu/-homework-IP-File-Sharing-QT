#ifndef SERVERCONNECTIONTHREAD_H
#define SERVERCONNECTIONTHREAD_H

#include "utils.h"
#include "server.h"
#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>

class ServerConnectionThread : public QThread
{

	Q_OBJECT

public:
	ServerConnectionThread(QObject *parent, int socketDescriptor);
	~ServerConnectionThread();

	void run();

private:
	int socketDescriptor;
	QObject *parent;

};

#endif // SERVERCONNECTIONTHREAD_H
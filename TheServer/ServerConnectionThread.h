#ifndef SERVERCONNECTIONTHREAD_H
#define SERVERCONNECTIONTHREAD_H

#include "utils.h"
#include "server.h"
#include <QByteArray>
#include <QThread>
#include <QTcpSocket>

class ServerConnectionThread : public QThread
{

	Q_OBJECT

public:
	ServerConnectionThread(QObject *parent, int socketDescriptor, QObject *server, QMutex *lock);
	~ServerConnectionThread();

	void run();

	QMutex *lock;

private:
	int socketDescriptor;
	QObject *server;

};

#endif // SERVERCONNECTIONTHREAD_H
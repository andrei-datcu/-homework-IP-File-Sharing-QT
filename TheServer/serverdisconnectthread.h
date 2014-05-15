#ifndef SERVERDISCONNECTTHREAD_H
#define SERVERDISCONNECTTHREAD_H

#include <QThread>
#include "utils.h"
#include "server.h"

class ServerDisconnectThread : public QThread
{
	Q_OBJECT

public:
	ServerDisconnectThread(QObject *parent = NULL);
	ServerDisconnectThread(QObject *parent, int socketDescriptor, QObject *server, QMutex *lock);
	~ServerDisconnectThread();

	void run();
	QMutex *lock;

private:
	int socketDescriptor;
	QObject *server;
};

#endif // SERVERDISCONNECTTHREAD_H

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

public slots:
	void bytesWritten(qint64 bytes);

private:
	int socketDescriptor;
	QObject *server;
};

#endif // SERVERDISCONNECTTHREAD_H
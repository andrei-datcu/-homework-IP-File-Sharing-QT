#ifndef REQUESTTHREAD_H
#define REQUESTTHREAD_H

#include "ShareFileSystem.h"

#include <QObject>
#include <QTcpSocket>
#include <QThread>

class RequestThread : public QThread
{
	Q_OBJECT

public:
	RequestThread(QObject *parent, int socketDescriptor, ShareFileSystem &share);
	~RequestThread();
	
	void run();

	public slots:
		void startRead();

private:
	int socketDescriptor;
	ShareFileSystem &share;
	
};

#endif // REQUESTTHREAD_H

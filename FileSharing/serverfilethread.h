#ifndef SERVERFILETHREAD_H
#define SERVERFILETHREAD_H

#include "ShareFileSystem.h"

#include <QObject>
#include <QThread>
#include <QTcpSocket>

class ServerFileThread : public QThread
{
	Q_OBJECT

public:
	ServerFileThread(QObject *parent, int socketDescriptor, ShareFileSystem &share);
	~ServerFileThread();

	void run();

private:
	int socketDescriptor;
	ShareFileSystem &share;
	
};

#endif // SERVERFILETHREAD_H

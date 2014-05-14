#ifndef SERVERDISCONNECTWRAPPER_H
#define SERVERDISCONNECTWRAPPER_H

#include <QObject>
#include <QTcpServer>
#include "serverdisconnectthread.h"

class ServerDisconnectWrapper : public QTcpServer
{
	Q_OBJECT

public:
	ServerDisconnectWrapper(QObject *parent = NULL);
	~ServerDisconnectWrapper();
	
protected:
	void incomingConnection(qintptr socketDescriptor);

private:
	QObject *server;
	
};

#endif // SERVERDISCONNECTWRAPPER_H

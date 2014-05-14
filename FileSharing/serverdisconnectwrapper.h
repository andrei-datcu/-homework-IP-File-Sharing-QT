#ifndef SERVERDISCONNECTWRAPPER_H
#define SERVERDISCONNECTWRAPPER_H

#include <QTcpServer>
#include <QMutex>

class ServerDisconnectWrapper : public QTcpServer
{
	Q_OBJECT

public:
	ServerDisconnectWrapper(QObject *parent = NULL);
	ServerDisconnectWrapper(QObject *parent, QMutex *lock);
	~ServerDisconnectWrapper();

	QMutex *lock;

protected:
	void incomingConnection(qintptr socketDescriptor);

private:
	QObject *server;
};

#endif // SERVERDISCONNECTWRAPPER_H

#ifndef SERVERWRAPPER_H
#define SERVERWRAPPER_H

#include <QTcpServer>
#include <QMap>
#include <qobject.h>

class ServerWrapper : public QTcpServer
{
	Q_OBJECT

public:
	ServerWrapper(QObject *parent = NULL);
	~ServerWrapper();

protected:
	void incomingConnection(qintptr socketDescriptor);

private:
	QObject *server;
};

#endif // SERVERWRAPPER_H

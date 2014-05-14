#ifndef CLIENTDISCONNECTSERVERTHREAD_H
#define CLIENTDISCONNECTSERVERTHREAD_H

#include <QMap>
#include <QThread>
#include <QTcpSocket>
#include "utils.h"

class ClientDisconnectServerThread : public QThread
{
	Q_OBJECT

public:
	ClientDisconnectServerThread(QObject *parent, QString ipAddress, int portNumber, QString username);
	~ClientDisconnectServerThread();

	void run();

	QString ipAddress;
	int portNumber;
	
private:
	int socketDescriptor;
	QTcpSocket *peer;
	QString username;
	
};

#endif // CLIENTDISCONNECTSERVERTHREAD_H

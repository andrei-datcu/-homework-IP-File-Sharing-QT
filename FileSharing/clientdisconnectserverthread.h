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
	ClientDisconnectServerThread(QObject *parent);
	~ClientDisconnectServerThread();

	void run();

	public slots:
		void readyRead();
		void connected();
		void disconnected();
		void bytesWritten(qint64 bytes);

private:
	int socketDescriptor;
	QTcpSocket *peer;
	QString username;
	
};

#endif // CLIENTDISCONNECTSERVERTHREAD_H

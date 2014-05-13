#ifndef CLIENTCONNECTSERVERTHREAD_H
#define CLIENTCONNECTSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "utils.h"
#include <QMap>

class ClientConnectServerThread : public QThread
{
	Q_OBJECT

public:
	ClientConnectServerThread(QObject *parent, QString ipAddress, int portNumber, QString username);
	~ClientConnectServerThread();

	QString ipAddress;
	int portNumber;

	void run();
	void doConnect();
	void loginToServer();
	void makeRequest();
	void getUserList();

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

#endif // CLIENTCONNECTSERVERTHREAD_H

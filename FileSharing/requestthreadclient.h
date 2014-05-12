#pragma once
#include "qthread.h"
#include <QObject>
#include <QTcpSocket>
#include <QThread>

class RequestThreadClient : public QThread
{

	Q_OBJECT

public:
	RequestThreadClient(QObject *parent);
	~RequestThreadClient(void);

	void run();
	void doConnect();
	void makeRequest();

	public slots:
		void readyRead();
		void connected();
		void disconnected();
		void bytesWritten(qint64 bytes);


private:
	int socketDescriptor;
	QTcpSocket *peer;
};


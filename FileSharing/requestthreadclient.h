#pragma once
#include "qthread.h"
#include "ShareFileSystem.h"
#include <QObject>
#include <QTcpSocket>
#include <QThread>

class RequestThreadClient : public QThread
{

	Q_OBJECT

public:
	RequestThreadClient(QObject *parent);
	RequestThreadClient(QObject *parent, QString ipAddress, int portNumber, int type, ShareFileSystem **share);
	~RequestThreadClient(void);

	QString ipAddress;
	int portNumber;
	int type;

	void run();
	bool doConnect();
	void getFileList();

signals:
    void errorAtConnection();

	public slots:
		void readyRead();
		void connected();
		void disconnected();
		void bytesWritten(qint64 bytes);


private:
	int socketDescriptor;
	QTcpSocket *peer;
	ShareFileSystem **share;
};


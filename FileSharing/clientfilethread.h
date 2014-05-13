#ifndef CLIENTFILETHREAD_H
#define CLIENTFILETHREAD_H

#include <QThread>
#include <QObject>
#include <QTcpSocket>

class ClientFileThread : public QThread
{
	Q_OBJECT

public:
	ClientFileThread(QObject *parent, QString ipAddress, int portNumber, int fileID);
	~ClientFileThread();
	void run();
	void doConnect();
	void getFile();
	void downloadFile();

	public slots:
		//void readyRead();
		void connected();
		void disconnected();
		void bytesWritten(qint64 bytes);

signals:
		void gotBytes(int bytesNumber);

private:
	QString ipAddress;
	int portNumber;
	int fileID;
	QTcpSocket *peer;


	
};

#endif // CLIENTFILETHREAD_H

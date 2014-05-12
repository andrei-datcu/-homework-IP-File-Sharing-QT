#ifndef REQUESTTHREAD_H
#define REQUESTTHREAD_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>

class RequestThread : public QThread
{
	Q_OBJECT

public:
	RequestThread(QObject *parent, int socketDescriptor);
	~RequestThread();
	
	void run();

	public slots:
		void startRead();

private:
	int socketDescriptor;
	
};

#endif // REQUESTTHREAD_H

#ifndef CLIENTRESPONDTOSEARCHTHREAD_H
#define CLIENTRESPONDTOSEARCHTHREAD_H

#include <QThread>

class ClientRespondToSearchThread : public QThread
{
	Q_OBJECT

public:
	ClientRespondToSearchThread(QObject *parent, int socketDescriptor, QObject *user);
	~ClientRespondToSearchThread();

	void run();

private:
	int socketDescriptor;
	QObject *user;
	
};

#endif // CLIENTRESPONDTOSEARCHTHREAD_H

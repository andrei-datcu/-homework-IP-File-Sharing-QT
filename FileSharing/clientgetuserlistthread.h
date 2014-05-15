#ifndef CLIENTGETUSERLISTTHREAD_H
#define CLIENTGETUSERLISTTHREAD_H

#include <QThread>
#include <QTcpSocket>


class ClientGetUserListThread : public QThread
{
	Q_OBJECT

public:
	ClientGetUserListThread(QObject *parent, int socketDescriptor, QObject *user);
	~ClientGetUserListThread();

	void run();

private:
	QObject *user;
	int socketDescriptor;
};

#endif // CLIENTGETUSERLISTTHREAD_H

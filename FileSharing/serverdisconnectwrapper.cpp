#include "serverdisconnectwrapper.h"
#include "serverdisconnectthread.h"

ServerDisconnectWrapper::ServerDisconnectWrapper(QObject *parent)
	: QTcpServer(parent),
	server(parent)
{

}

ServerDisconnectWrapper::ServerDisconnectWrapper(QObject *parent, QMutex *lock)
	: QTcpServer(parent),
	server(parent),
	lock(lock)
{

}

ServerDisconnectWrapper::~ServerDisconnectWrapper()
{

}

void ServerDisconnectWrapper::incomingConnection(qintptr socketDescriptor)
{
	ServerDisconnectThread *thread = new ServerDisconnectThread(this, socketDescriptor, server, lock);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}
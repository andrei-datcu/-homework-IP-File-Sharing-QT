#include "serverdisconnectwrapper.h"

ServerDisconnectWrapper::ServerDisconnectWrapper(QObject *parent)
	: QTcpServer(parent),
	server(parent)
{

}

ServerDisconnectWrapper::~ServerDisconnectWrapper()
{

}

void ServerDisconnectWrapper::incomingConnection(qintptr socketDescriptor)
{
	ServerDisconnectThread *thread = new ServerDisconnectThread(this, socketDescriptor, server);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}
#include "clientrespondtosearchserver.h"
#include "clientrespondtosearchthread.h"

ClientRespondToSearchServer::ClientRespondToSearchServer(QObject *parent)
	: QTcpServer(parent),
	user(parent)
{

}

ClientRespondToSearchServer::~ClientRespondToSearchServer()
{

}

void ClientRespondToSearchServer::incomingConnection(qintptr socketDescriptor)
{
	ClientRespondToSearchThread *thread = new ClientRespondToSearchThread(this, socketDescriptor, user);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}

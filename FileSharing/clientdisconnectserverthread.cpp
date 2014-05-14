#include "clientdisconnectserverthread.h"

ClientDisconnectServerThread::ClientDisconnectServerThread(QObject *parent)
	: QThread(parent)
{

}

ClientDisconnectServerThread::~ClientDisconnectServerThread()
{

}


void ClientDisconnectServerThread::run()
{
	peer = new QTcpSocket();
}
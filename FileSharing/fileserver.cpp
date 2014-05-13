#include "fileserver.h"
#include "serverfilethread.h"

FileServer::FileServer(QObject *parent,ShareFileSystem &share)
	: QTcpServer(parent),
	share(share)
{

}

FileServer::~FileServer()
{

}

void FileServer::incomingConnection(qintptr socketDescriptor)
{
	ServerFileThread * thread = new ServerFileThread(this, socketDescriptor, share);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();

}

#include "peer.h"
#include "ShareFileSystem.h"
#include "requestthreadclient.h"
#include "clientfilethread.h"
#include "utils.h"

#define REQ_FILELIST

Peer::Peer(QString username, QString ipAddress, int portNumber, QObject *parent)
	: QObject(parent), 
	username(username),
	ipAddress(ipAddress),
	portNumber(portNumber)
{

}

Peer::~Peer()
{

}


RequestThreadClient* Peer::getFileList()
{
	RequestThreadClient *thread = new RequestThreadClient(this, ipAddress, portNumber, 0, &fs);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
	return thread;
}

ClientFileThread* Peer::getFile(int fileID)
{
	ClientFileThread *thread = new ClientFileThread(this, ipAddress, FILEPORT, fileID);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
	return thread;
}

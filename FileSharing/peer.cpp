#include "peer.h"
#include "ShareFileSystem.h"
#include "requestthreadclient.h"
#include "clientfilethread.h"
#include "utils.h"

#define REQ_FILELIST

Peer::Peer(QString username, QString ipAddress, QObject *parent)
	: QObject(parent), 
	username(username),
	ipAddress(ipAddress)
{

}

Peer::~Peer()
{

}


RequestThreadClient* Peer::getFileList()
{
	RequestThreadClient *thread = new RequestThreadClient(this, ipAddress, FILELISTPORT, 0, &fs);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
	return thread;
}

ClientFileThread* Peer::getFile(int fileID, QString downloadPath)
{
	ClientFileThread *thread = new ClientFileThread(this, ipAddress, FILEPORT, fileID, downloadPath);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
	return thread;
}

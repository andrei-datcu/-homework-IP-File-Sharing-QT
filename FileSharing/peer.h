#ifndef PEER_H
#define PEER_H
#include "ShareFileSystem.h"
#include "clientfilethread.h"
#include "requestthreadclient.h"
#include <QObject>
#include <QThread>

class Peer : public QObject
{
	Q_OBJECT

public:
	Peer(QString username, QString ipAddress, QObject *parent=0);
	~Peer();
	QString username, ipAddress;

	RequestThreadClient* getFileList();
	ClientFileThread* getFile(int fileID, QString downloadPath);

    ShareFileSystem* fs;
	
};

#endif // PEER_H

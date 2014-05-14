#ifndef PEER_H
#define PEER_H
#include "ShareFileSystem.h"
#include "clientfilethread.h"
#include <QObject>
#include <QThread>

class Peer : public QObject
{
	Q_OBJECT

public:
	Peer(QString username, QString ipAddress, int portNumber, QObject *parent=0);
	~Peer();
	QString username, ipAddress;
	int portNumber;

	RequestThreadClient* getFileList();
	ClientFileThread* getFile(int fileID);

    ShareFileSystem* fs;
	
};

#endif // PEER_H

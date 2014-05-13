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

	ShareFileSystem* getFileList();
	ClientFileThread* getFile(int fileID);



private:
	
};

#endif // PEER_H

#include "serveruserlistupdatethread.h"

ServerUserlistUpdateThread::ServerUserlistUpdateThread(QObject *parent, QMap<QString, QString> userList, QString newUser)
	: QThread(parent),
	userList(userList),
	newUser(newUser)
{

}

ServerUserlistUpdateThread::~ServerUserlistUpdateThread()
{

}

void ServerUserlistUpdateThread::run()
{
	QTcpSocket *peer;

	for(QMap<QString, QString>::iterator it=userList.begin(); it != userList.end(); it++) {
		if (it.key() != newUser) {
			peer = new QTcpSocket();
			peer->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
			peer->connectToHost(it.value(), UPDATEPORT);
			if (!peer->waitForConnected(5000))
				qDebug()<<"[SERVER] Error connecting to UPDATEPORT...";
		
			qDebug() << "Sending updated UserList to" << it.key();
			QByteArray transfer = toByteArray(userList);
			int size = transfer.count();

			peer->write((char *)&size, sizeof(int));
			peer->write(transfer);

			peer->waitForBytesWritten(5000);
			peer->close();
		}
	}
}

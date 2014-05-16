#ifndef CLIENTSEARCHTHREAD_H
#define CLIENTSEARCHTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QMap>
#include <vector>
#include <tuple>

class ClientSearchThread : public QThread
{
	Q_OBJECT

public:
	ClientSearchThread(QObject *parent, QString searchName);
	~ClientSearchThread();

	void run();
	void doConnect(QString ipAddress);
	void doTheSearch(QString peerUserName);

private:
	QObject *user;
	QString searchName;
	QTcpSocket *peer;
	std::vector<std::tuple<QString, int, int, QString>> results;
	int size;
	QByteArray data;
	
};

#endif // CLIENTSEARCHTHREAD_H

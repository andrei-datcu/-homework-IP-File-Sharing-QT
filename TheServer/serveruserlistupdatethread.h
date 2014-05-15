#ifndef SERVERUSERLISTUPDATETHREAD_H
#define SERVERUSERLISTUPDATETHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QMap>
#include <QDebug>

#include "utils.h"
#include "util_serializer.h"

class ServerUserlistUpdateThread : public QThread
{
	Q_OBJECT

public:
	ServerUserlistUpdateThread(QObject *parent, QMap<QString, QString> userList, QString newUser);
	~ServerUserlistUpdateThread();

	void run();

	QString ipAddress;
	int portNumber;

private:
	QMap<QString, QString> userList;
	QString newUser;

};

#endif // SERVERUSERLISTUPDATETHREAD_H

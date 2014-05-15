#ifndef CLIENTRESPONDTOSEARCHSERVER_H
#define CLIENTRESPONDTOSEARCHSERVER_H

#include <QTcpServer>

class ClientRespondToSearchServer : public QTcpServer
{
	Q_OBJECT

public:
	ClientRespondToSearchServer(QObject *parent);
	~ClientRespondToSearchServer();

protected:
	void incomingConnection(qintptr socketDescriptor);

private:
	QObject *user;
};

#endif // CLIENTRESPONDTOSEARCHSERVER_H

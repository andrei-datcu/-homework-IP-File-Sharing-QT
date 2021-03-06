#ifndef USER_H
#define USER_H
#include "fileresolvserver.h"
#include "fileserver.h"
#include "ShareFileSystem.h"
#include "clientconnectserverthread.h"
#include "clientdisconnectserverthread.h"
#include "clientgetuserlistserver.h"
#include "clientrespondtosearchserver.h"
#include "clientsearchthread.h"


#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

class User : public QObject
{
	Q_OBJECT

public:
	User(QString username, QObject *parent = 0);
	QString username;
	QMap<QString, QString> userList;
	std::vector<std::tuple<QString, int, int, QString>> searchResult;
    //username - id - size - filename
	bool usernameOk;
	void startListeningFilelist();
	void startListeningFile();
	void startListeningUserList();
	void startListeningSearch();

	ClientConnectServerThread* connectToServer(QString ipAddress, int portNumber = SERVERPORT);
	ClientDisconnectServerThread* disconnectFromServer();
	ClientSearchThread* searchFile(QString searchName);
	~User();

    ShareFileSystem *shared;


    FileResolvServer *fileListServer;

	public slots:
		void test_slot();

signals:
	void gotNewUserList();
	void gotSearchResults();


private:
	FileServer *fileServer;
	ClientGetUserListServer *userListServer;
	ClientRespondToSearchServer *searchServer;
	int numberIn;
    QString serverIp;
    int serverPortNo;
	
};

#endif // USER_H

#include "clientsearchthread.h"
#include "utils.h"
#include "util_serializer.h"
#include "user.h"
#include <QByteArray>

ClientSearchThread::ClientSearchThread(QObject *parent, QString searchName)
	: QThread(parent),
	searchName(searchName),
	user(parent)
{
	data = searchName.toLatin1();
	size = data.count();
}

ClientSearchThread::~ClientSearchThread()
{

}

void ClientSearchThread::run()
{
	User *the_user = (User*) user;
	QMap<QString, QString>::iterator i;
	for (i=the_user->userList.begin(); i!=the_user->userList.end(); ++i)
	{
		peer = new QTcpSocket();
		doConnect(i.value());
		doTheSearch(i.key());
	}

	peer->waitForReadyRead(3000);
}

void ClientSearchThread::doConnect(QString ipAddress)
{
	qDebug()<<"Ii cer lui "<<ipAddress << SEARCHPORT;
	peer->connectToHost(ipAddress, SEARCHPORT);
	if (!peer->waitForConnected(5000))
		qDebug()<<"Error at Connecting...";
}

void ClientSearchThread::doTheSearch(QString peerUserName)
{
	int new_size;
	char buffer[4000];
	std::list<std::tuple<int, int, QString>> oneResult;

	writeToSocket(peer, (char*)&size, sizeof(int));
	writeToSocket(peer, data.data(), size);
	peer->waitForReadyRead(-1);

	readFromSocket(peer, buffer, sizeof(int));
	memcpy(&new_size, buffer, sizeof(int));
	qDebug()<<"Got something for you"<<new_size;

	if (new_size != 0)
	{
		
		readFromSocket(peer, buffer, new_size);
		QByteArray recvData(buffer, new_size);
		oneResult = searchResultsFromByteArray(recvData);
		if (oneResult.size() > 0)
		{
			std::list<std::tuple<int, int, QString>>::iterator i;
			int tuple_size, tuple_fileid;
			QString tuple_filename; 
			for (auto item: oneResult)
			{
				std::tie(tuple_fileid, tuple_size, tuple_filename) = item;
				qDebug()<<tuple_fileid<<tuple_size<<tuple_filename;
				results.push_back(std::make_tuple(peerUserName, tuple_fileid, tuple_size, tuple_filename));
			}
			User *the_user = (User*) user;
			the_user->searchResult = results;
			emit the_user->gotSearchResults();
		}
	}
	
}

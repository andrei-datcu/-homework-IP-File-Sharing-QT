#include "user.h"
#include "requestthread.h"
#include "requestthreadclient.h"
#include "fileresolvserver.h"
#include "utils.h"
#include <windows.h>

#include <QDebug>

User::User(QString username, QObject *parent)
	: QObject(parent),
	  username(username),
	  server(this)
{


}

void User::startListening()
{
	if (!server.listen(QHostAddress::Any, 8888))
	{
		qDebug()<<"Serverul nu asculta";
	}
	else
		qDebug()<<"Serverul asculta\n";
}


void User::makeRequest()
{
	RequestThreadClient *thread = new RequestThreadClient(this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();

}


User::~User()
{
	server.close();
	free(in_socket);
	free(out_socket);

}

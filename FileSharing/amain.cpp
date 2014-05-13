#include "ShareFileSystem.h"
#include "sharedriveeditorwidget.h"
#include <QApplication>
#include <qstring.h>
#include "server.h"
#include "utils.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
	/*
    ShareFileSystem sfs(QString("test.json"));
    //ShareDriveView w(sfs);

    ShareDriveEditorWidget w(sfs);
    w.show();

    a.exec();

    sfs.saveToFile("test.json");
	*/
	Server srv;
	srv.listen(QHostAddress::Any, 8888);
	QMap<QString, QString> userList;
	UsernameResponse rsp;

	qDebug("Starting...");

	QTcpSocket sck;
	sck.connectToHost("127.0.0.1", 8888);
	Username usr;
	strcpy(usr.ipAddress, "10.10.10.10");
	strcpy(usr.userName, "Tedy");
	char buffer[1000];
	memcpy(buffer, &usr, sizeof(Username));
	sck.write(buffer, sizeof(Username));

	if (sck.waitForReadyRead(5000)) 
		qDebug("Ready for read!");
	else
		qDebug("Timeout!");

	sck.read(buffer, sizeof(UsernameResponse));
	memcpy(&rsp, buffer, sizeof(UsernameResponse));

	//qDebug() << "[Client]" << rsp.valid << " " << rsp.size;


	a.exec();
    return 0;
}

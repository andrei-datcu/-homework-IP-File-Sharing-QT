#include "ShareFileSystem.h"
#include "qt_windows.h"
#include "sharedriveeditorwidget.h"
#include <QApplication>
#include <qstring.h>
#include "server.h"
#include "utils.h"
#include "user.h"

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

	//qDebug() << "[Client]" << rsp.valid << " " << rsp.size;

	Server srv;
	srv.startListeningConnectServer();
	srv.startListeningDisconnectServer();

	User myUsr("Tudor");
	//myUsr.connectToServer("127.0.0.1", SERVERPORT);
	myUsr.disconnectFromServer("127.0.0.1", SERVERPORT + 1);

	a.exec();
    return 0;
}

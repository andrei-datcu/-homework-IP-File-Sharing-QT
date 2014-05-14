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

	//qDebug() << "[Client]" << rsp.valid << " " << rsp.size;

	Server srv;
	srv.startListeningConnectServer();
	//srv.startListeningDisconnectServer();

	

	a.exec();
    return 0;
}

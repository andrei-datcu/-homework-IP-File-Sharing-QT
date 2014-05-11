#include "ShareFileSystem.h"
#include "sharedriveeditorwidget.h"
#include <QApplication>
#include <qstring.h>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    ShareFileSystem sfs(QString("test.json"));
    //ShareDriveView w(sfs);

    ShareDriveEditorWidget w(sfs);
    w.show();

    a.exec();

    sfs.saveToFile("test.json");
    return 0;
}

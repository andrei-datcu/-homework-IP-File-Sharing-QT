#include "downloadwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DownloadWindow w;
    w.show();
    return a.exec();
}

#ifndef FILEEXPLORERVIEW_H
#define FILEEXPLORERVIEW_H

#include <QTableView>
#include <qfilesystemmodel.h>

class FileExplorerView : public QTableView
{
    Q_OBJECT

public:
    FileExplorerView(QWidget *parent = 0);
    ~FileExplorerView();

    QString getCurrentPath();
    QFileSystemModel *filemodel;
};

#endif // FILEEXPLORERVIEW_H

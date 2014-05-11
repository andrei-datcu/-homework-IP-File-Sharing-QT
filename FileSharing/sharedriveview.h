#ifndef SHAREDRIVEVIEW_H
#define SHAREDRIVEVIEW_H

#include <QTableView>
#include "ShareFileSystem.h"
#include "filesystemmodel.h"
#include <list>

class ShareDriveView : public QTableView
{
    Q_OBJECT

public:
    ShareDriveView(ShareFileSystem &fs, QWidget *parent = 0);
    FileTree *getCurrentDirectory();
    std::list<FileTree *> getSelectedItems();
    void refreshView();

    FileSystemModel *model;

private:

    ShareFileSystem &fs;
};

#endif // SHAREDRIVEVIEW_H

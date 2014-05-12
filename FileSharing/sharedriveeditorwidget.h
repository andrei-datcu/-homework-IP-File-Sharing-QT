#ifndef SHAREDRIVEEDITORWIDGET_H
#define SHAREDRIVEEDITORWIDGET_H

#include <QWidget>
#include <qpushbutton.h>
#include <forward_list>

#include "sharedriveview.h"
#include "fileexplorerview.h"
#include "ShareFileSystem.h"

class ShareDriveEditorWidget : public QWidget
{
    Q_OBJECT

public:
    ShareDriveEditorWidget(ShareFileSystem &fs, QWidget *parent = 0);
    ~ShareDriveEditorWidget();

private:

    ShareFileSystem &fs;
    ShareDriveView *shareView;
    FileExplorerView *computerView;

    QPushButton *shareFileButton, *createDirButton, *deleteButton, *renameButton;

    std::forward_list<FileTree*> delitems;
};

#endif // SHAREDRIVEEDITORWIDGET_H

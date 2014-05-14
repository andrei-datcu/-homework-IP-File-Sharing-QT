#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QWidget>
#include "sharedriveview.h"
#include "fileexplorerview.h"
#include "ShareFileSystem.h"
#include "peer.h"
#include <qpushbutton.h>
#include "downloadspogresswidget.h"

class DownloadWidget : public QWidget
{
    Q_OBJECT

public:
    DownloadWidget(Peer &peer, DownloadsPogressWidget *progressWidget,
                   QWidget *parent = 0);
    ~DownloadWidget();

private:
    
    Peer &peer;
    ShareDriveView *peerview;
    FileExplorerView *localview;

    QPushButton *downloadbutton;
    DownloadsPogressWidget *progressWidget;
};

#endif // DOWNLOADWIDGET_H

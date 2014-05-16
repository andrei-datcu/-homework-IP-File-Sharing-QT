#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "downloadwidget.h"
#include <qtabwidget.h>
#include <vector>
#include "peer.h"
#include "downloadspogresswidget.h"
#include "sharedriveeditorwidget.h"
#include "user.h"

#include "searchfilewidget.h"
#include "usersdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    public slots:
        void addPeer(Peer *p);

private:
    
    QTabWidget *tabWidget;
    DownloadsPogressWidget *progresswidget;
    ShareDriveEditorWidget *shareeditorwidget;
    std::vector<Peer*> activePeers;
    User myUser;

    UsersDialog *uDialog;
    SearchFileWidget *searchWidget;
    QAction *connectToServerAction;

    int searchTabPos;
};

#endif // MAINWINDOW_H

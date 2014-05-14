#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "downloadwidget.h"
#include <qtabwidget.h>
#include <vector>
#include "peer.h"
#include "downloadspogresswidget.h"
#include "user.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    
    QTabWidget *tabWidget;
    DownloadsPogressWidget *progresswidget;
    std::vector<Peer*> activePeers;
    User myUser;
};

#endif // MAINWINDOW_H

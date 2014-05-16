#include "mainwindow.h"

#include <qmenu.h>
#include <qmenubar.h>
#include <qaction.h>
#include <qinputdialog.h>
#include <qprogressdialog.h>
#include "peer.h"
#include "requestthreadclient.h"
#include <qsplitter.h>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), myUser(""), searchTabPos(-1){


    QMenu *mymenu = new QMenu("My System", this);
    QMenu *servermenu = new QMenu("Sever", this);
    QMenu *peersmenu = new QMenu("Peers", this);
	menuBar()->addMenu(mymenu);
    menuBar()->addMenu(servermenu);
    menuBar()->addMenu(peersmenu);

	QAction *a;
	a = new QAction("Connect to a user...", this);
	connect(a, &QAction::triggered, [this](){
        bool ok;
        QString text = QInputDialog::getText(this, "Connect to a user...",
                                          "User:", QLineEdit::Normal,
                                          "", &ok);

        if (ok && !text.isEmpty()){
            Peer *user = new Peer("p2puser", text);
            addPeer(user);
        }
    });
	peersmenu->addAction(a);

    QAction *editDriveAction = new QAction("Edit your share drive...", this);
    connect(myUser.fileListServer, &FileResolvServer::shareRequested, [this](){
        this->editDriveAction->setEnabled(false);
    });
    shareeditorwidget = new ShareDriveEditorWidget(*(myUser.shared), this);

    connect(editDriveAction, SIGNAL(triggered()), shareeditorwidget, SLOT(exec()));
    mymenu->addAction(editDriveAction);


    connectToServerAction = new QAction("Connect to server...", this);
    connectToServerAction->setEnabled(false);
    connect(connectToServerAction, &QAction::triggered, [this](){
        bool ok;
        QString text = QInputDialog::getText(this, "Connect to server...",
                                          "Server:", QLineEdit::Normal,
                                          "", &ok);

        if (ok && !text.isEmpty()){

            QProgressDialog *pd = new QProgressDialog(this);
            pd->setRange(0, 0);
            pd->setLabelText("Waiting for server's response...");
            ClientConnectServerThread* cst =  myUser.connectToServer(text);
            connect(cst, SIGNAL(finished()), pd, SLOT(close()));
            pd->exec();
            if (!myUser.usernameOk)
                QMessageBox::critical(0,"Error","Username already taken. Please choose another one!");
            else{
                QMessageBox::information(0,"Ok","Connection successful");
                uDialog->populateList();
            }
                   
        }
    });
    servermenu->addAction(connectToServerAction);

    uDialog = new UsersDialog(myUser, this);

    connect(&myUser, SIGNAL(gotNewUserList()), uDialog, SLOT(populateList())); 

    QAction *a4 = new QAction("Search users...", this);
    servermenu->addAction(a4);
    connect(a4, &QAction::triggered, [this](){
        uDialog->exec();
        if (uDialog->result() == QDialog::Accepted){
            addPeer(uDialog->selectedPeer);
        }
    });

    QAction *a5 = new QAction("Set username", this);
    servermenu->addAction(a5);
    connect(a5, &QAction::triggered, [this](){
        bool ok;
        QString text = QInputDialog::getText(this, "Set your username...",
                                          "Username:", QLineEdit::Normal,
                                          myUser.username, &ok);

        if (ok && !text.isEmpty()){
            myUser.username = text;
            connectToServerAction->setEnabled(true);
        }
    });




    QAction *a6 = new QAction("Search file...", this);
    servermenu->addAction(a6);
    connect(a6, &QAction::triggered, [this](){
        if (searchTabPos != -1)
            tabWidget->setCurrentIndex(searchTabPos);
        else{
            tabWidget->addTab(searchWidget, "Search files...");
            searchTabPos = tabWidget->count() - 1;
        }
    });

    progresswidget = new DownloadsPogressWidget(this);
    searchWidget = new SearchFileWidget(myUser, progresswidget, this);
    searchWidget->setVisible(false);

    tabWidget = new QTabWidget(this);
    tabWidget->setMinimumHeight(300);
    tabWidget->setTabsClosable(true);

    connect(tabWidget, &QTabWidget::tabCloseRequested, [this](const int &index){

        if (index == searchTabPos){
            tabWidget->removeTab(index);
            searchTabPos = -1;
            return;
        }

        if (QMessageBox::question(this, "Confirmation", "Are you sure?", 
                     QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
            return; //user clicked no

        int realIndex = index - (index > searchTabPos && searchTabPos != -1 ? 1 : 0);

        activePeers.erase(activePeers.begin() + realIndex);
        tabWidget->removeTab(realIndex);
    });

    QSplitter *qsp = new QSplitter(this);
    qsp->setOrientation(Qt::Vertical);
    qsp->addWidget(tabWidget);
    qsp->addWidget(progresswidget);
    setCentralWidget(qsp);
}

MainWindow::~MainWindow(){

    if (myUser.usernameOk){
        myUser.disconnectFromServer()->wait();
    }
}


void MainWindow::addPeer(Peer *user){

    QProgressDialog *pd = new QProgressDialog(this);
    pd->setRange(0, 0);
    pd->setLabelText("Waiting for user's response...");

    RequestThreadClient *rtc =  user->getFileList();  
    connect(rtc, SIGNAL(finished()), pd, SLOT(accept()));
    if (pd->exec() != QDialog::Accepted)
        return;

    if (user->fs == NULL){
        QMessageBox::critical(this, "Error", "Cannot conect to user. Make sure you've written the right ip");
        return;
    }
    tabWidget->addTab(new DownloadWidget(*user, progresswidget, this), user->username);
    activePeers.push_back(user);
}
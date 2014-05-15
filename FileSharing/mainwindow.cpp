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
    : QMainWindow(parent), myUser(""){

    QMenu *menu = new QMenu("File", this);
	menuBar()->addMenu(menu);

	QAction *a;
	a = new QAction("Connect to a user...", this);
	connect(a, &QAction::triggered, [this](){
        bool ok;
        QString text = QInputDialog::getText(this, "Connect to a user...",
                                          "User:", QLineEdit::Normal,
                                          "", &ok);

        if (ok && !text.isEmpty()){
            Peer *user = new Peer("bla", text);
            activePeers.push_back(user);
            QProgressDialog *pd = new QProgressDialog(this);
            pd->setRange(0, 0);
            pd->setLabelText("Waiting for user's response...");

            RequestThreadClient *rtc =  user->getFileList();           
            connect(rtc, SIGNAL(finished()), pd, SLOT(close()));
            pd->exec();
            tabWidget->addTab(new DownloadWidget(*user, progresswidget, this), user->username);

        }
    });
	menu->addAction(a);

    QAction *a2 = new QAction("Edit your share drive...", this);
    shareeditorwidget = new ShareDriveEditorWidget(*(myUser.shared), this);

    connect(a2, SIGNAL(triggered()), shareeditorwidget, SLOT(exec()));
    menu->addAction(a2);


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
    menu->addAction(connectToServerAction);

    uDialog = new UsersDialog(myUser, this);
    QAction *a4 = new QAction("Search users...", this);
    menu->addAction(a4);
    connect(a4, &QAction::triggered, [this](){
        if (uDialog->exec()){
            activePeers.push_back(uDialog->selectedPeer);
            QProgressDialog *pd = new QProgressDialog(this);
            pd->setRange(0, 0);
            pd->setLabelText("Waiting for user's response...");

            RequestThreadClient *rtc =  uDialog->selectedPeer->getFileList();           
            connect(rtc, SIGNAL(finished()), pd, SLOT(close()));
            pd->exec();
            tabWidget->addTab(new DownloadWidget(*uDialog->selectedPeer, progresswidget, this), uDialog->selectedPeer->username);
        }
    });

    QAction *a5 = new QAction("Set username", this);
    menu->addAction(a5);
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



    progresswidget = new DownloadsPogressWidget(this);
    tabWidget = new QTabWidget(this);
    tabWidget->setMinimumHeight(300);

    QSplitter *qsp = new QSplitter(this);
    qsp->setOrientation(Qt::Vertical);
    qsp->addWidget(tabWidget);
    qsp->addWidget(progresswidget);
    setCentralWidget(qsp);
}

MainWindow::~MainWindow()
{

}

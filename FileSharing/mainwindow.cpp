#include "mainwindow.h"

#include <qmenu.h>
#include <qmenubar.h>
#include <qaction.h>
#include <qinputdialog.h>
#include <qprogressdialog.h>
#include "peer.h"
#include "requestthreadclient.h"
#include <qsplitter.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), myUser("gogu"){

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
            tabWidget->addTab(new DownloadWidget(*user, progresswidget, this), user->username);
            QProgressDialog *pd = new QProgressDialog(this);
            pd->setRange(0, 0);
            pd->setLabelText("Waiting for user's response...");

            RequestThreadClient *rtc =  user->getFileList();
            
            connect(rtc, SIGNAL(finished()), pd, SLOT(close()));
        }
    });
	menu->addAction(a);

    progresswidget = new DownloadsPogressWidget(this);
    tabWidget = new QTabWidget(this);

    QSplitter *qsp = new QSplitter(this);
    qsp->setOrientation(Qt::Vertical);
    qsp->addWidget(tabWidget);
    qsp->addWidget(progresswidget);
    setCentralWidget(qsp);
    setMinimumHeight(500);
}

MainWindow::~MainWindow()
{

}

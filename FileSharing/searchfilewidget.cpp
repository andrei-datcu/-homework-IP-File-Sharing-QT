#include "searchfilewidget.h"
#include <qlayout.h>
#include <qlabel.h>
#include <qprogressdialog.h>
#include <qtablewidget.h>
#include <qheaderview.h>
#include <qfiledialog.h>
#include <qsplitter.h>
#include <tuple>
#include <qmessagebox.h>
#include "downloadspogresswidget.h"

#include <peer.h>

SearchFileWidget::SearchFileWidget(User &u, DownloadsPogressWidget *pw, QWidget *parent)
    : QWidget(parent), myUser(u), progressWidget(pw){

    QVBoxLayout *lookupLayout = new QVBoxLayout(this);
    QHBoxLayout *sLayout = new QHBoxLayout(this);
    sLayout->addWidget(new QLabel("Search keyword:", this));
    searchWordEdit = new QLineEdit(this);
    sLayout->addWidget(searchWordEdit);

    lookupLayout->addLayout(sLayout);

    searchButton = new QPushButton("Search", this);
    lookupLayout->addWidget(searchButton);
    connect(searchButton, &QAbstractButton::clicked, [this](){
        QProgressDialog *pd = new QProgressDialog(this);
        pd->setRange(0, 0);
        pd->setLabelText("Gathering search results...");
        auto cst =  myUser.searchFile(searchWordEdit->text());
        connect(cst, SIGNAL(finished()), pd, SLOT(accept()));
        if (pd->exec() != QDialog::Accepted)
            return;

        resultListWidget->clearContents();

        for (auto sRes : myUser.searchResult){

            QString fileName, userName;
            int fSize;

            std::tie(userName, std::ignore, fSize, fileName) = sRes;
            QTableWidgetItem *fNameItem = new QTableWidgetItem(fileName);
            QTableWidgetItem *fSizeItem = new QTableWidgetItem(QString::number(fSize));
            QTableWidgetItem *uNameItem = new QTableWidgetItem(userName);
            
            int rIndex = resultListWidget->rowCount();
            resultListWidget->insertRow(rIndex);
            resultListWidget->setItem(rIndex, 0, fNameItem);
            resultListWidget->setItem(rIndex, 1, fSizeItem);
            resultListWidget->setItem(rIndex, 2, uNameItem);
        }
    });

    resultListWidget = new QTableWidget(0, 3, this);
    resultListWidget->setShowGrid(false);
    resultListWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    resultListWidget->setSelectionMode(QAbstractItemView::SingleSelection);  
    QStringList tableHeaders;
    tableHeaders.append("File name");
    tableHeaders.append("File size");
    tableHeaders.append("User name");
    resultListWidget->setHorizontalHeaderLabels(tableHeaders);
    resultListWidget->verticalHeader()->setVisible(false);
 
    connect(resultListWidget, &QTableWidget::cellDoubleClicked, [this](int r, int c){
        int fileId, fileSize;
        QString userName, fileName;

        std::tie(userName, fileId, fileSize, fileName) = myUser.searchResult[r];

        Peer *p = new Peer(userName, myUser.userList[userName]);

        QString dir = QFileDialog::getExistingDirectory(this, "Select Directory",
                             QString(), QFileDialog::ShowDirsOnly);
        if (!dir.endsWith("/"))
                    dir += "/";

        qDebug() << dir << "\n";

        QString savePath = dir + fileName;

        QFileInfo fi(savePath);
        if (fi.exists())
            if (QMessageBox::question(this, "Overwrite", "File " + fileName + " will be overwritten. Do you want to proceed?",
                        QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
                        return;

        QFile f(savePath);
        if (!f.open(QIODevice::WriteOnly)){
            QMessageBox::warning(this, "Error", "Cannot save any file here. Please make sure you have the right permissions or choose another directory");
            return;
        }

        ClientFileThread *dwnthread = p->getFile(fileId, savePath);
        connect(dwnthread, &ClientFileThread::connectionFailed, [this](const QString& fn){
               QMessageBox::critical(this, "Error", "Connection failed! File " + fn + " could not be downloaded. Probably user exited");
        });
        progressWidget->addFileProgressTrack(fileName, fileSize, dwnthread);
    });

    QSplitter *sp = new QSplitter(this);
    QWidget *lookupWidget = new QWidget(this);
    lookupWidget->setLayout(lookupLayout);
    sp->addWidget(lookupWidget);
    sp->addWidget(resultListWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(sp);
    setLayout(mainLayout);
}

SearchFileWidget::~SearchFileWidget()
{

}

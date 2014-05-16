#include "downloadwidget.h"
#include <qlayout.h>
#include <qsplitter.h>
#include <qmessagebox.h>

DownloadWidget::DownloadWidget(Peer &peer, DownloadsPogressWidget *progressWidget,
                               QWidget *parent)
    : QWidget(parent), peer(peer){

    this->progressWidget = progressWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);
    QSplitter *sp = new QSplitter(this);
    mainLayout->addWidget(sp);
    
    localview = new FileExplorerView(this);
    sp->addWidget(localview);

    peerview = new ShareDriveView(*(peer.fs), this);
    sp->addWidget(peerview);

    QHBoxLayout *buttonsLayout = new QHBoxLayout(this);
    mainLayout->addLayout(buttonsLayout);

    downloadbutton = new QPushButton("Download", this);
    buttonsLayout->addWidget(downloadbutton);
    connect(downloadbutton, &QAbstractButton::clicked, [this](){

        std::list<FileTree*> selItems = peerview->getSelectedItems();

        for (FileTree* item : selItems)
            if (!item->finfo.dir){
                QString curPath = localview->getCurrentPath();
                if (!curPath.endsWith("/"))
                    curPath += "/";
                QString savePath = curPath + item->finfo.name;

                QFileInfo fi(savePath);
                if (fi.exists())
                    if (QMessageBox::question(this, "Overwrite", "File " + item->finfo.name + " will be overwritten. Do you want to proceed?",
                        QMessageBox::Yes | QMessageBox::No) == QMessageBox::No)
                        continue;

                QFile f(savePath);
                if (!f.open(QIODevice::WriteOnly)){
                    QMessageBox::warning(this, "Error", "Cannot save any file here. Please make sure you have the right permissions or choose another directory");
                    return;
                }
                ClientFileThread *dwnthread = this->peer.getFile(item->finfo.index, savePath);
                this->progressWidget->addFileProgressTrack(item->finfo.name, item->finfo.size, dwnthread);
            }
    });
}

DownloadWidget::~DownloadWidget()
{

}

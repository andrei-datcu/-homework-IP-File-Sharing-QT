#include "downloadwidget.h"
#include <qlayout.h>
#include <qsplitter.h>

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
                QString savePath = localview->getCurrentPath() + QString("/") + item->finfo.name;
                ClientFileThread *dwnthread = this->peer.getFile(item->finfo.index, savePath);
                this->progressWidget->addFileProgressTrack(item->finfo.name, item->finfo.size, dwnthread);
            }
    });
}

DownloadWidget::~DownloadWidget()
{

}

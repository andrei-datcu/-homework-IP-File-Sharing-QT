#include "sharedriveview.h"
#include <qheaderview.h>

ShareDriveView::ShareDriveView(ShareFileSystem &fs, QWidget *parent)
    : QTableView(parent), fs(fs){

    model = new FileSystemModel(fs.getRoot(), this);    
    setModel(model);

    connect(this, &QAbstractItemView::doubleClicked, [this](const QModelIndex &index){

        FileTree *item = model->getItem(index);

        if (item->finfo.dir){
            this->setRootIndex(model->setCurrentFromIndex(index));
        }
    });

    setShowGrid(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    verticalHeader()->setVisible(false);
}

FileTree* ShareDriveView::getCurrentDirectory(){
    return model->currentItem();
}

void ShareDriveView::refreshView(){

    model->revert();
    reset();
    setRootIndex(model->setCurrentItem(model->currentItem()));
    model->revert();
}

std::list<FileTree*> ShareDriveView::getSelectedItems(){

    std::list<FileTree*> result;
    QModelIndexList slst = selectionModel()->selectedRows();

    for (QModelIndex &index : slst)
        result.push_front(model->getItem(index));

    return result;
}
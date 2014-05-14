#include "fileexplorerview.h"
#include <qfileinfo.h>
#include <qheaderview.h>

FileExplorerView::FileExplorerView(QWidget *parent)
    : QTableView(parent){

    filemodel = new QFileSystemModel(this);
    filemodel->setFilter(QDir::AllEntries | QDir::NoDot);
    setModel(filemodel);

    setRootIndex(filemodel->setRootPath(filemodel->myComputer().toString()));
    setShowGrid(false);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);

    connect(this, &QAbstractItemView::doubleClicked, [this](const QModelIndex &index){

        QFileInfo fi = filemodel->fileInfo(index);

        if (fi.isDir())
            setRootIndex(filemodel->setRootPath(fi.absoluteFilePath()));
    });

    verticalHeader()->setVisible(false);
}

FileExplorerView::~FileExplorerView()
{

}


QString FileExplorerView::getCurrentPath(){

    return filemodel->fileInfo(currentIndex()).absoluteFilePath();
}
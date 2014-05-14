#include "sharedriveeditorwidget.h"
#include <qlayout.h>
#include <qsplitter.h>
#include <qpushbutton.h>
#include <qfileinfo.h>
#include <qinputdialog.h>

ShareDriveEditorWidget::ShareDriveEditorWidget(
    ShareFileSystem &fs,
    QWidget *parent): fs(fs){

    shareView =  new ShareDriveView(fs, this);
    computerView = new FileExplorerView(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QSplitter *mainSp = new QSplitter(this);

    mainLayout->addWidget(mainSp);

    mainSp->addWidget(computerView);
    mainSp->addWidget(shareView);

    QHBoxLayout *buttonsLayout = new QHBoxLayout(this);
    mainLayout->addLayout(buttonsLayout);

    shareFileButton = new QPushButton("Share File", this);
    shareFileButton->setEnabled(false);
    buttonsLayout->addWidget(shareFileButton);
    connect(shareFileButton, &QAbstractButton::pressed, [this](){

        QFileInfo fi = computerView->filemodel->fileInfo(computerView->selectionModel()->selectedRows().at(0));
        this->fs.addFile(fi.absoluteFilePath(), shareView->getCurrentDirectory());
        shareView->refreshView();
    });

    createDirButton = new QPushButton("New Folder", this);
    buttonsLayout->addWidget(createDirButton);
    connect(createDirButton, &QAbstractButton::pressed, [this](){

        bool ok;
        QString text = QInputDialog::getText(this, "Create new folder...",
                                          "Folder name:", QLineEdit::Normal,
                                          "New Folder", &ok);

        if (ok && !text.isEmpty()){
            this->fs.createFolder(text, shareView->getCurrentDirectory());
            shareView->refreshView();
        }
    });

    deleteButton = new QPushButton("Delete", this);
    deleteButton->setEnabled(false);
    buttonsLayout->addWidget(deleteButton);
    connect(deleteButton, &QAbstractButton::pressed, [this](){
        QModelIndexList selected = shareView->selectionModel()->selectedRows();
        for (QModelIndex &i : selected){
            FileTree *item = shareView->model->getItem(i);
            this->fs.removeTree(item);
            delitems.push_front(item);
        }
        shareView->refreshView();
    });


    renameButton = new QPushButton("Rename", this);
    renameButton->setEnabled(false);
    buttonsLayout->addWidget(renameButton);
    connect(renameButton, &QAbstractButton::pressed, [this](){
        std::list<FileTree*> selItems = shareView->getSelectedItems();

        if (selItems.size() != 1) //We can rename only one
            return;

        bool ok;
        QString text = QInputDialog::getText(this, "Rename...",
                                          "New name:", QLineEdit::Normal,
                                          selItems.front()->finfo.name, &ok);

        if (ok && !text.isEmpty()){
            selItems.front()->finfo.name = text;
            shareView->refreshView();
        }
    });

    connect(computerView->selectionModel(), &QItemSelectionModel::selectionChanged,
        [this](const QItemSelection &, const QItemSelection &){

            bool enable_buttons = computerView->selectionModel()->selectedRows().size() != 0;
            bool p2 = true;
            QModelIndexList sellst = computerView->selectionModel()->selectedRows();
            for (QModelIndex &index : sellst)
                p2 = p2 && !computerView->filemodel->fileInfo(index).isDir();

            shareFileButton->setEnabled(p2 && enable_buttons);
            
    });

    connect(shareView->selectionModel(), &QItemSelectionModel::selectionChanged,
        [this](const QItemSelection &, const QItemSelection &){

            bool enable_buttons = shareView->selectionModel()->selectedRows().size() != 0;
            deleteButton->setEnabled(enable_buttons);
            renameButton->setEnabled(enable_buttons);
    });

    connect(computerView, &QAbstractItemView::doubleClicked,
        [this](){
            shareFileButton->setEnabled(false);
        }
    );

    connect(shareView, &QAbstractItemView::doubleClicked,
        [this](){
            deleteButton->setEnabled(false);
            renameButton->setEnabled(false);
        }
    );

}

ShareDriveEditorWidget::~ShareDriveEditorWidget(){

    for (FileTree* item:delitems)
        delete(item);
}

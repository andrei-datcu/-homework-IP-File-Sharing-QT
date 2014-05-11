#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QAbstractItemModel>
#include <qfileiconprovider.h>
#include "FileTree.h"

class FileSystemModel : public QAbstractItemModel
{
Q_OBJECT
 
public:
    static enum Column{NAME, SIZE, TYPE, DATE, LASTCOLUMN};

    FileSystemModel(FileTree *root, QObject* parent = NULL);
    ~FileSystemModel();
 
    QVariant headerData(int section, Qt::Orientation orientation, int role)
        const;
 
    Qt::ItemFlags flags(const QModelIndex &index) const; 
    int columnCount(const QModelIndex & /* parent */) const;
 
    int rowCount(const QModelIndex &parent) const;
 
    QVariant data(const QModelIndex &index, int role) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex index(const QString& path, int column = 0) const;
    QModelIndex parent(const QModelIndex &index) const;

 
    QModelIndex setCurrentFromIndex(const QModelIndex& index);
    QModelIndex setCurrentItem (FileTree *item);
  
    FileTree *getItem(const QModelIndex &index) const;
    FileTree *currentItem();

private:
    static QIcon iconFromFileInfo(const FileInfo &info);
    static QString typeFromFileInfo(const FileInfo &info);

    static QFileIconProvider iconProvider;

    FileTree *mRootItem, *mCurrentItem;
    QStringList mHeaders;
};

#endif // FILESYSTEMMODEL_H

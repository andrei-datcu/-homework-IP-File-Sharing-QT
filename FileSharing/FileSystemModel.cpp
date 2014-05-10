#include "filesystemmodel.h"
#include "FileTree.h"
#include <qabstractitemmodel.h>
#include <qpixmap.h>
#include <qpixmapcache.h>
#include <qt_windows.h>
#include <qdebug.h>
#include <QtWinExtras/qwinfunctions.h>

QFileIconProvider FileSystemModel::iconProvider;

FileSystemModel::FileSystemModel(FileTree *root, QObject* parent)
    : QAbstractItemModel(parent), mIconFactory(new QFileIconProvider()),
    mRootItem(root), mCurrentItem(root){
        // Now it is time to fix the headers
        mHeaders << "Name"
            << "Size"
            << "Type"
            << "Date Modified";

}

FileSystemModel::~FileSystemModel(){
    delete mIconFactory;
}

QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const{

    if(orientation == Qt::Horizontal){
        switch(role){
            // in case of DisplayRole, just return the header text
        case Qt::DisplayRole:
            return mHeaders.at(section);
            break;
            // in case of TextAlignmentRole, only SIZE column will be right align,
            // others will be left align
        case Qt::TextAlignmentRole:
            return int(SIZE) == section ? Qt::AlignRight : Qt::AlignLeft;
            break;
        }
    }

    return QVariant();
}

Qt::ItemFlags FileSystemModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return 0;

    // Our model is read only.
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

int FileSystemModel::columnCount(const QModelIndex & /* parent */) const{
    return LASTCOLUMN; // here it is; 4.
}

int FileSystemModel::rowCount(const QModelIndex &parent) const{
    FileTree *parentItem = getItem(parent);
    return parentItem->childCount() + 1;
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const{
    // invalid work, invalid return
    if (!index.isValid()){
        return QVariant();
    }

    // in case of TextAlignmentRole, only SIZE column will be right align,
    // others will be left align
    if(int(SIZE) == index.column() && Qt::TextAlignmentRole == role){
        return Qt::AlignRight;
    }

    // At present, I don't want pay attention other than DisplayRole & DecorationRole
    if (role != Qt::DisplayRole && role != Qt::DecorationRole){
        return QVariant();
    }

    FileTree *item = getItem(index);

    if(!item){
        return QVariant();
    }

    // if the role is for decoration & column is zero, we send the item's icon
    if(role == Qt::DecorationRole && index.column() == int(NAME) ){
        return iconFromFileInfo(item->finfo);
    }

    QVariant data;
    Column col = Column(index.column());

    switch(col){
    case NAME:
        data = index.row() ? item->finfo.name : "..";
        break;
    case SIZE:
        if(item->finfo.dir){
            data = ""; // we don't want to show zero.
        }
        else{
            data = item->finfo.size;
        }
        break;
    case TYPE:
        data = typeFromFileInfo(item->finfo);
        break;
    case DATE:
        //data = item->fileInfo().lastModified().toString(Qt::LocalDate);
        break;
    default:
        data = "";
        break;
    }

    return data;
}

QModelIndex FileSystemModel::index(int row, int column, const QModelIndex &parent) const{

    // As the NAME column is a tree, we will only create index which parent is NAME column
    if (parent.isValid() && parent.column() != int(NAME))
        return QModelIndex();

    FileTree *parentItem = getItem(parent);

    // if there is a parent index, we want to work
    if(parentItem){
        if (row == 0)
            return createIndex(row, column, parentItem);
        FileTree *childItem = parentItem->childAt(row - 1);

        if (childItem){
            return createIndex(row, column, childItem);
        }
    }

    return QModelIndex();
}

QModelIndex FileSystemModel::index(const QString& path, int column) const{

    if(path.length() > 0){
        FileTree *item = mRootItem->getTreeFromPath(path);

        if(item){
            return createIndex(item->myIndexInParentList(),column,item);
        }
    }

    return QModelIndex();
}

QModelIndex FileSystemModel::parent(const QModelIndex &index) const{

    // invalid work, invalid return
    if(!index.isValid()){
        return QModelIndex();
    }

    FileTree* childItem = getItem(index);

    // If there is no child, there is no index
    if(!childItem){
        return QModelIndex();
    }

    FileTree *parentItem = index.row() ? childItem->parent : childItem;

    // if there is no parent or parent is invisible, there is no index
    if (!parentItem || parentItem == mRootItem){
        return QModelIndex();
    }

    return createIndex(parentItem->myIndexInParentList(), NAME, parentItem);
}

QModelIndex FileSystemModel::setCurrentFromIndex(const QModelIndex& index){

    FileTree *item = getItem(index);

    if (index.row() == 0) // Daca am apasat pe ..
        item = item->parent;

    if (item){
        mCurrentItem = item;
        return createIndex(item->myIndexInParentList(), 0, item);
    }
    return QModelIndex();
}

QModelIndex FileSystemModel::setCurrentItem (FileTree *item){

    mCurrentItem = item;
    QModelIndex ret = createIndex(item->myIndexInParentList(), 0, item);
    return ret;
}

FileTree* FileSystemModel::getItem(const QModelIndex &index) const{
    // just return the internal pointer we set at creating index if the index is valid
    if(index.isValid()) {
        FileTree *item = static_cast<FileTree*>(index.internalPointer());

        if(item) {
            return item;
        }
    }
    return mRootItem;
}

QIcon FileSystemModel::iconFromFileInfo(const FileInfo &info){

    static QPixmapCache iconCache;

    QFileInfo fileInfo(info.name);
    QPixmap pixmap;


    if (info.dir)
        return iconProvider.icon(QFileIconProvider::Folder);

#ifdef Q_OS_WIN32

    if (fileInfo.suffix().isEmpty() ||
        fileInfo.suffix() == "exe" && fileInfo.exists())
        return iconProvider.icon(fileInfo);


    if (!iconCache.find(fileInfo.suffix(), &pixmap)){
        // Support for nonexistent file type icons, will reimplement it as custom icon provider later
        /* We don't use the variable, but by storing it statically, we
        * ensure CoInitialize is only called once. */
        static HRESULT comInit = CoInitialize(NULL);
        Q_UNUSED(comInit);

        SHFILEINFO shFileInfo;
        unsigned long val = 0;

        val = SHGetFileInfo((const wchar_t *)("foo." + fileInfo.suffix()).utf16(), 0, &shFileInfo,
            sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_USEFILEATTRIBUTES);

        // Even if GetFileInfo returns a valid result, hIcon can be empty in some cases
        if (val && shFileInfo.hIcon)
        {
            pixmap = QtWin::fromHICON(shFileInfo.hIcon);
            if (!pixmap.isNull())
                iconCache.insert(fileInfo.suffix(), pixmap);
            DestroyIcon(shFileInfo.hIcon);
        }
        else{
            // TODO: Return default icon if nothing else found
        }
    }

#else
    // Default icon for Linux and Mac OS X for now
    return iconProvider.icon(fileInfo);
#endif
    return QIcon(pixmap);
}

QString FileSystemModel::typeFromFileInfo(const FileInfo &info){

    SHFILEINFOA shFileInfo;
    unsigned long val = 0;

    if (info.dir)
        return "Directory";

    QFileInfo fileInfo(info.name);

    val = SHGetFileInfoA((const char *)("foo." + fileInfo.suffix()).toUtf8().constData(), 0, &shFileInfo,
        sizeof(SHFILEINFO), SHGFI_TYPENAME | SHGFI_USEFILEATTRIBUTES);

    // Even if GetFileInfo returns a valid result, hIcon can be empty in some cases
    if (val)
        return QString(shFileInfo.szTypeName);
    else
        return "";
}
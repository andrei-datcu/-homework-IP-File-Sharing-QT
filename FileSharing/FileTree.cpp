#include "FileTree.h"
#include <qstringlist.h>
#include <QList>

const QString FileTree::delim = "/";
int FileInfo::total = 0;

FileTree::FileTree(FileInfo finfo, FileTree* parent) :
    finfo(finfo), parent(parent){

	if (parent != NULL) {
		parent->addChild(this);
	}
}

void FileTree::addChild(FileTree *child) {
	children.push_front(child);
}

void FileTree::addFileIt(const FileInfo &finfo,
                         const QList<QString>::iterator &begin,
                         const QList<QString>::iterator &end) {

	if (begin == end) { //Daca lista e goala begin==end
		new FileTree(finfo, this);
		return;
	}

	for(FileTree *ch : children) {
		if (ch->getName() == *begin)
			return ch->addFileIt(finfo, begin + 1, end);
	}

}

void FileTree::addFile(const QString &realPath,
                       const QString &fullPath) {
	QStringList list = fullPath.split(delim, QString::SkipEmptyParts);
    FileInfo fi(realPath);
	addFileIt(fi, list.begin(), list.end());
}

void FileTree::addDirectory(const QString &dirName,
                            const QString &fullPath) {

    QStringList list = fullPath.split(delim, QString::SkipEmptyParts);
    FileInfo fi(dirName, 0, true);
    addFileIt(fi, list.begin(), list.end());
}

QString FileTree::getName() {
	return finfo.name;
}

FileTree::~FileTree(void){
	for (FileTree* ch : children)
		delete ch;
}

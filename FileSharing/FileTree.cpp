#include "FileTree.h"
#include <qstringlist.h>
#include <QList>

const QString FileTree::delim = "/";
int FileInfo::total = 0;

FileTree::FileTree(FileInfo finfo, FileTree* parent) : finfo(finfo), parent(parent)
{
	if (parent != NULL) {
		parent->addChild(this);
	}
}

void FileTree::addChild(FileTree *child) {
	children.push_back(child);
}

void FileTree::addFileIt(FileTree* root, const FileInfo &finfo, const QList<QString>::iterator &begin, const QList<QString>::iterator &end) {
	if (begin + 1 == end) {
		new FileTree(finfo, root);
		return;
	}

	for(FileTree *ch : children) {
		if (ch->getName() == *begin)
			return addFileIt(ch, finfo, begin + 1, end);
	}

}

void FileTree::addFile(FileTree* root, const QString &fullPath) {
	QStringList list = fullPath.split(delim, QString::SkipEmptyParts);
	
}

void FileTree::addDirectory(FileTree* root, const QString &fullPath) {

}

QString FileTree::getName() {
	return finfo.name;
}

FileTree::~FileTree(void)
{
	for (FileTree* ch : children)
		delete ch;
}

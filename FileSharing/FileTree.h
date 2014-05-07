#pragma once

#include <QJSonArray>
#include <forward_list>
#include <qfileinfo.h>

struct FileInfo
{
	static int total;

	FileInfo(const QString &name, int size, bool dir) :
			name(name), size(size), dir(dir) {

		index = total++;
	}

	FileInfo(const QString &realFullPath) {
		QFileInfo qfi(realFullPath);
		name = qfi.fileName();
		size = qfi.size();
		dir = qfi.isDir();
		index = total++;
	}

	QString name;
	bool dir;
	int size;
	int index;
};


class FileTree
{
public:
	static const QString delim;
	FileInfo finfo;
	FileTree *parent;
	std::forward_list<FileTree*> children;

	QString getName();
	void addChild(FileTree* child);
	void addFile(const QString &realPath, const QString &fullPath);
	void addDirectory(const QString &dirName, const QString &fullPath);
	FileTree(FileInfo _finfo, FileTree* parent);
	~FileTree(void);
private:
	void addFileIt(const FileInfo &finfo,
                   const QList<QString>::iterator &begin,
                   const QList<QString>::iterator &end);
	
};


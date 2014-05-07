#pragma once

#include <QJSonArray>
#include <vector>
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
	int index
};


class FileTree
{
public:
	static const QString delim;
	FileInfo finfo;
	FileTree *parent;
	std::vector<FileTree*> children;

	QString getName();
	void addChild(FileTree* child);
	void addFile(FileTree* root, const QString &fullPath);
	void addDirectory(FileTree* root, const QString &fullPath);
	FileTree(FileInfo _finfo, FileTree* parent);
	~FileTree(void);
private:
	void addFileIt(FileTree* root, const FileInfo &finfo, const QList<QString>::iterator &begin, const QList<QString>::iterator &end);
	
};


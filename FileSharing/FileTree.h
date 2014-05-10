#pragma once

#include <QJSonArray>
#include <vector>
#include <qfileinfo.h>

struct FileInfo
{
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

private:
    static int total;
};


class FileTree
{
public:
	static const QString delim;
	const FileInfo finfo;
	FileTree *parent;
	std::vector<FileTree*> children;

    FileTree(FileInfo _finfo, FileTree* parent);
	~FileTree(void);

	QString getName();
    int childCount() const;
    int myIndexInParentList() const;
    FileTree* childAt(int index);
    FileTree* getTreeFromPath(const QString &path);
	void addChild(FileTree* child);
	void addFile(const QString &realPath, const QString &fullPath);
	void addDirectory(const QString &dirName, const QString &fullPath);

private:
	void addFileIt(const FileInfo &finfo,
                   const QList<QString>::iterator &begin,
                   const QList<QString>::iterator &end);

    FileTree* getTreeIt(const QList<QString>::iterator &begin,
                        const QList<QString>::iterator &end);
	
};


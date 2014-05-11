#pragma once

#include <qjsonobject.h>
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

    FileInfo(const QJsonObject &json){
        name = json["name"].toString();
        size = json["size"].toInt();
        dir = json["dir"].toBool();
        index = json["index"].toInt();
    }

	QString name;
	bool dir;
	int size;
	int index;

    QJsonObject toJson(){

        QJsonObject result;
        result["name"] = name;
        result["size"] = size;
        result["dir"] = dir;
        result["index"] = index;

        return result;
    }


    static int total;
};


class FileTree
{
public:
	static const QString delim;
	FileInfo finfo;
	FileTree *parent;
	std::vector<FileTree*> children;

    FileTree(FileInfo _finfo, FileTree* parent);
    FileTree(const QJsonObject &object, FileTree *parent);
	~FileTree(void);

	QString getName();
    int childCount() const;
    int myIndexInParentList() const;
    FileTree* childAt(int index);
    FileTree* getTreeFromPath(const QString &path);
	void addChild(FileTree* child);
	int addFile(const QString &realPath, const QString &fullPath="");
	void addDirectory(const QString &dirName, const QString &fullPath="");
    void removeTree();

    QJsonObject toJson();

private:
	void addFileIt(const FileInfo &finfo,
                   const QList<QString>::iterator &begin,
                   const QList<QString>::iterator &end);

    FileTree* getTreeIt(const QList<QString>::iterator &begin,
                        const QList<QString>::iterator &end);
	
};


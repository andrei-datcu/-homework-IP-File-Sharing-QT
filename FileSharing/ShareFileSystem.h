#pragma once

#include "FileTree.h"
#include <unordered_map>

class ShareFileSystem
{
public:
    ShareFileSystem(void);
    ShareFileSystem(const QString &fileName);
    ShareFileSystem(const QByteArray &bytes);
    ~ShareFileSystem(void);

    FileTree* getRoot();

    void addFile(const QString &realFullPath, FileTree *directory);
    void removeTree(FileTree *t);
    void createFolder(const QString &folderName, FileTree *parent);
	void getFilePath(int index);

    void saveToFile(const QString &fileName);
    QByteArray toByteArray();

private:

    void fillFromBytesArray(const QByteArray &bytes);
    FileTree *root;
    std::unordered_map<int, QString> fileIds;
};


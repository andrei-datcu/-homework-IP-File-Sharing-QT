#include "filesystem.h"


FileSystem::FileSystem() 
{
	nrFiles = 0;
}


void FileSystem::addFile(const QString &filePath)
{
	QJsonObject newFile;
	QFileInfo qfi(filePath);

	newFile.insert(QString("index"), nrFiles);
	newFile.insert(QString("size"), qfi.size());

	filePaths.insert(nrFiles++, qfi.filePath());

	fileList.insert(qfi.fileName(), newFile);
}


QString FileSystem::getFilePath(int index)
{
	return filePaths.value(index);
}


QJsonObject FileSystem::getFileList()
{
	return fileList;
}


QString FileSystem::fileListToString()
{
	return QJsonValue(fileList).toString();
}


QJsonObject FileSystem::fileListFromString(const QString &jsonString)
{
	return QJsonValue(jsonString).toObject();
}

QStringList FileSystem::getListOfFiles()
{
	return fileList.keys();
}

FileSystem::~FileSystem()
{

}
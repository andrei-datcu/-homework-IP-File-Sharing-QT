#include "filesystem.h"


FileSystem::FileSystem() 
{
	nrFiles = 0;
	fileList = new QJsonObject();
	fileList->insert("files", QJsonArray());
	fileList->insert("dirName", QString("root"));
}


void FileSystem::addFile(const QString &file, const QString &relativePath)
{
	QJsonObject newFile, newDir, *temp = fileList;
	QFileInfo qfi(file);

	QStringList tokens = relativePath.split("/", QString::SkipEmptyParts);

	//qDebug() << "fileName: " << qfi.fileName();
	for (QString &s : tokens) {
		//qDebug() << s;
		if (s != qfi.fileName()) {
			if (temp->contains(s)) {
				temp = &temp->value(s).toObject();
			} else {
				newDir = QJsonObject();
				newDir.insert("dirName", s);
				newDir.insert("size", -1);
				newDir.insert("files", QJsonArray());
				temp->insert(s, newDir);
				temp = &temp->value(s).toObject();
			}
		}
	}


	newFile.insert("index", nrFiles);
	newFile.insert("size", qfi.size());
	newFile.insert("name", qfi.fileName());

	if (temp->contains("files")) {
		QJsonArray files = temp->value("files").toArray();
		files.insert(files.size(), newFile);
		temp->insert("files", files);
	}
	
	fileList = temp;
	filePaths.insert(nrFiles++, qfi.filePath());

	//fileList.insert(qfi.fileName(), newFile);
}


QString FileSystem::getFilePath(int index)
{
	return filePaths.value(index);
}


QJsonObject FileSystem::getFileList()
{
	//qDebug() << "Blabla1\n";
	QJsonObject result = *fileList;
	//qDebug() << "Blabla2\n";
	return result;
}


QString FileSystem::fileListToString()
{
	return QJsonValue(*fileList).toString();
}


QJsonObject FileSystem::fileListFromString(const QString &jsonString)
{
	return QJsonValue(jsonString).toObject();
}

QStringList FileSystem::getListOfFiles()
{
	return fileList->keys();
}

FileSystem::~FileSystem()
{
	delete fileList;
}
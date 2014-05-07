#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>
#include <QJsonObject>
#include <QStringList>
#include <QMap>
#include <QFileInfo>
#include <QJsonArray>
#include <QDebug>

class FileSystem : public QObject
{
	Q_OBJECT

public:
	FileSystem();
	QJsonObject getFileList();
	QString getFilePath(int index);
	QString fileListToString();
	QJsonObject fileListFromString(const QString &jsonString);
	QStringList getListOfFiles();
	void addFile(const QString &file, const QString &relativePath);
	~FileSystem();

private:
	QJsonObject *fileList;
	QMap<int, QString> filePaths;
	int nrFiles;
	
};

#endif // FILESYSTEM_H

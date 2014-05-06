#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>

class FileSystem : public QObject
{
	Q_OBJECT

public:
	FileSystem(QObject *parent);
	~FileSystem();

private:
	
};

#endif // FILESYSTEM_H

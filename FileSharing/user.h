#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
	Q_OBJECT

public:
	User(QObject *parent);
	~User();

private:
	
};

#endif // USER_H

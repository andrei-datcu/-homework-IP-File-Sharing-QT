#include "util_serializer.h"

#include <QDebug>


QByteArray toByteArray(QMap<QString, QString> lista)
{
	QJsonObject json;
	QJsonArray userList;

	for (QMap<QString, QString>::iterator i=lista.begin(); i!=lista.end(); i++)
	{
		QJsonObject fjson;
		fjson["username"] = i.key();
		fjson["address"] = i.value();
		userList.append(fjson);
	}
	json["userlist"] = userList;
	QJsonDocument jdoc(json);
	QByteArray result = jdoc.toJson();

	return result;
}

QMap<QString, QString> fromByteArray(const QByteArray &bytes)
{
	QMap<QString, QString> result;
	QJsonDocument jdoc(QJsonDocument::fromJson(bytes));
	QJsonObject json = jdoc.object();
	QJsonArray userList = json["userlist"].toArray();

	for (const QJsonValue &v : userList)
		result.insert(v.toObject()["username"].toString(), v.toObject()["address"].toString());

	return result;
	

}


bool readFromSocket(QTcpSocket *socket, char*buffer, int byteCount)
{
	int bytesRead = 0;
	while (byteCount > 0)
	{
		bytesRead = socket->read(buffer, byteCount);
		if (bytesRead == -1)
			return false;
		buffer += bytesRead;
		byteCount -= bytesRead;
	}

	return true;
}

bool writeToSocket(QTcpSocket *socket, char *buffer, int byteCount)
{
	int bytesWritten = 0;
	while (byteCount > 0)
	{
		bytesWritten = socket->write(buffer, byteCount);
		if (bytesWritten == -1)
			return false;
		buffer += bytesWritten;
		byteCount -= bytesWritten;
	}

	return true;
}
#include "util_serializer.h"


QByteArray toByteArray(QMap<QString, QString> lista)
{
	QJsonObject json;
	QJsonArray userList;
	QMap<QString, QString>::iterator i;
	for (i=lista.begin(); i!=lista.end(); i++)
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
	for (const QJsonValue &v : userList) {
		result.insert(v.toObject()["username"].toString(), v.toObject()["address"].toString());
	}
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

QByteArray searchResultsToByteArray(const std::list<std::tuple<int, int, QString>> &l){

    QJsonArray a;

    for (auto item : l){
        QJsonObject jo;
        int id, size;
        QString fileName;
        std::tie(id, size, fileName) = item;
        jo["id"] = id;
        jo["size"]=size;
        jo["filename"] = fileName;
        a.append(jo);
    }

    QJsonObject obj;
    obj["items"] = a;

    QJsonDocument doc(obj);
    return doc.toJson();
}

std::list<std::tuple<int, int, QString>> searchResultsFromByteArray(const QByteArray &data){

    QJsonDocument doc(QJsonDocument::fromJson(data));

    QJsonObject mainObj = doc.object();
    QJsonArray arr = mainObj["items"].toArray();
    std::list<std::tuple<int, int, QString>> result;
    for (auto v : arr){
        QJsonObject o = v.toObject();
        result.push_back(std::make_tuple(o["id"].toInt(), o["size"].toInt(),o["filename"].toString())); 
    }

    return result;
}
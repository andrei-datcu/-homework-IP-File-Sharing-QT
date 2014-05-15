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
	for (const QJsonValue &v : userList)
		result.insert(v.toObject()["address"].toString(), v.toObject()["username"].toString());

	return result;
	

}
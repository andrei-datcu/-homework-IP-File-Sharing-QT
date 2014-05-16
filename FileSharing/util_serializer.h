#pragma once

#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qmap.h>
#include <qbytearray.h>
#include <qtcpsocket.h>
#include <list>
#include <tuple>

QByteArray toByteArray(QMap<QString, QString> lista);
QMap<QString, QString> fromByteArray(const QByteArray &bytes);
bool readFromSocket(QTcpSocket *socket, char *buffer, int byteCount);
bool writeToSocket(QTcpSocket *socket, char *buffer, int byteCount);

QByteArray searchResultsToByteArray(const std::list<std::tuple<int, int, QString>> &l);

std::list<std::tuple<int, int, QString>> searchResultsFromByteArray(const QByteArray &data);
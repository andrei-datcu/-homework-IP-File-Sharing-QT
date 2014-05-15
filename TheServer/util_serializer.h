#pragma once

#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qmap.h>
#include <qbytearray.h>


QByteArray toByteArray(QMap<QString, QString> lista);
QMap<QString, QString> fromByteArray(const QByteArray &bytes);
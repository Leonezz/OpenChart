/*
	Tool functions.
*/

#pragma once
#include <QObject>
#include <QList>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "JsonObject.h"
class DataProcess : public QObject
{
public:
	DataProcess(JsonObject* obj)
	{
		if (obj)
		{
			object = obj;
		}
	}
	QJsonObject dataForLine(const QList<QList<QVariant> >&);
	QString dataForBar(const QList<QList<QVariant> >&);
	QString dataForPie(const QList<QList<QVariant> >&);
	QString dataForScatter(const QList<QList<QVariant> >&);
	QString dataForRadar(const QList<QList<QVariant> >&);
	QString dataForTree(const QList<QList<QVariant> >&);
	QString dataForTreeMap(const QList<QList<QVariant> >&);
	QString dataForSun(const QList<QList<QVariant> >&);
	QString dataForBoxplot(const QList<QList<QVariant> >&);
	QString dataForHeatmap(const QList<QList<QVariant> >&);
	QString dataForParallelCoordinates(const QList<QList<QVariant> >&);
	QString dataForRelation(const QList<QList<QVariant> >&);
	QString dataForFunnel(const QList<QList<QVariant> >&);
	QString dataForRiver(const QList<QList<QVariant> >&);
	QString dataForScatter3D(const QList<QList<QVariant> >&);
	QString dataForBar3D(const QList<QList<QVariant> >&);
	QString dataForLine3D(const QList<QList<QVariant> >&);
	QString dataForSurface3D(const QList<QList<QVariant> >&);
	QString jsonToString(const QJsonObject&);

private:
	JsonObject* object;
};


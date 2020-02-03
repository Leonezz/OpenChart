/*
	Tool functions.
*/

#pragma once
#include <QList>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "JsonObject.h"
namespace DataProcess
{
	/*

	*/
	typedef std::size_t sizetype;
	void dataForLine(const QList<QList<QVariant> >&, JsonObject*);
	void dataForBar(const QList<QList<QVariant> >&, JsonObject*);
	void dataForPie(const QList<QList<QVariant> >&, JsonObject*);
	void dataForScatter(const QList<QList<QVariant> >&, JsonObject*);
	void dataForFlow(const QList<QList<QVariant> >&, JsonObject*);
	void dataForKLine(const QList<QList<QVariant> >&, JsonObject*);
	void dataForRadar(const QList<QList<QVariant> >&, JsonObject*);
	void dataForTree(const QList<QList<QVariant> >&, JsonObject*);
	void dataForTreeMap(const QList<QList<QVariant> >&, JsonObject*);
	void dataForSun(const QList<QList<QVariant> >&, JsonObject*);
	void dataForBoxplot(const QList<QList<QVariant> >&, JsonObject*);
	void dataForHeatmap(const QList<QList<QVariant> >&, JsonObject*);
	void dataForParallelCoordinates(const QList<QList<QVariant> >&, JsonObject*);
	void dataForSankey(const QList<QList<QVariant> >&, JsonObject*);
	void dataForRelation(const QList<QList<QVariant> >&, JsonObject*);
	void dataForFunnel(const QList<QList<QVariant> >&, JsonObject*);
	void dataForRiver(const QList<QList<QVariant> >&, JsonObject*);
	void dataForCalendar(const QList<QList<QVariant> >&, JsonObject*);
	void dataForDataSet(const QList<QList<QVariant> >&, JsonObject*);
	void dataForPolar(const QList<QList<QVariant> >&, JsonObject*);
	void dataForScatter3D(const QList<QList<QVariant> >&, JsonObject*);
	void dataForBar3D(const QList<QList<QVariant> >&, JsonObject*);
	void dataForLine3D(const QList<QList<QVariant> >&, JsonObject*);
	void dataForSurface3D(const QList<QList<QVariant> >&, JsonObject*);
	QString jsonToString(const QJsonObject&);
	inline void headerIndex(const QList<QVariant>& header, const QMap<QString, sizetype>& indexMap, 
		sizetype* indexs, bool* complete);
};

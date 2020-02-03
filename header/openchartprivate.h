#pragma once
#include <QtCore>
#include "JsonObject.h"
#include "filestream.h"
#include "QTreeWidget"
#include "QLabel"
class OpenChartPrivate:public QObject
{
	Q_OBJECT
public:
	OpenChartPrivate()
		:curChartIndex(0)
	{
		option = FileStream::readJson("./Resources/json/line.json");
		lastItem = new QTreeWidgetItem();
	}
	QString curChartType;
	QString filePath;
	int curChartIndex;
	QTreeWidgetItem* lastItem;
	QLabel* curChartLabel;
	JsonObject option;
	QJsonObject backup;
public slots:
	/*
	this class holds the very data of the chart,it requires a backup copy.
	//this function deals with the backup covery or enable stuff.
	this slot will be called when the html page load data,no matter success or not.
	*/
	void backStuff(const int error);
private:
	//cover and update the backup when successfully loaded.
	void coverBackUp();
	//enable the backup when error occured.
	void enableBackUp();
};



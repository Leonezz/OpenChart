#pragma once

#include <QtWidgets/QWidget>
#include <QTreeWidget>
#include <QDir>
#include <QUrl>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "ui_openchart_widget.h"
//#include "./Resources/codeFiles/charttypestring.h"
QT_BEGIN_NAMESPACE
namespace Ui {
	class OpenChart_demo;
}
QT_END_NAMESPACE

class OpenChart_demo : public QWidget
{
	Q_OBJECT

public:
	explicit OpenChart_demo(QWidget *parent = Q_NULLPTR);

	QJsonObject makeData(const QJsonObject& json);

	QJsonObject readJSON(const QString& name);
	void displayData();

public slots:
	void clicked();
	void reloadChart(QTreeWidgetItem* item,int column);

signals:
	void sendMsg(const QString& text);
	void showLoading();
	
private:
	QString jsonToString(const QJsonObject& jsonObj);
	void basicPlot(const QString& chartType);
private:
	Ui::OpenChart_demoClass ui;
};
typedef OpenChart_demo Widget;


#pragma execution_character_set("utf-8")	//set char-set to utf-8
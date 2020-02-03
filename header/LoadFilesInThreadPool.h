#pragma once
#include <qobject.h>
#include <QTreeWidget>
#include <qobject.h>
#include <QThread>
#include <qrunnable.h>
#include <QApplication>
#include <QJsonObject>
#include <QDebug>
const bool NOERROR = true;
const bool ERROR = false;
enum NowState {
	//this is actually the index of items on the treewidget.
	Line = 0,
	Bar = 1,
	CPie = 2,
	Scatter = 3,
	Flow = 4,
	KLine = 5,
	Radar = 6,
	BoxPlot = 7,
	HeatMap = 8,
	Relation = 9,
	Tree = 10,
	RectangleTree = 11,
	Sun = 12,
	ParallelCoordinateSystem = 13,
	Sankey = 14,
	Funnel = 15,
	Polar = 16,
	River = 17,
	Calendar = 18,
	Dataset = 19,
	D3Bar = 20,
	D3Scatter = 21,
	D3Surface = 22,
	D3Line = 23
};

class LoadFileTreeInThreadPool: public QObject,public QRunnable
{
	Q_OBJECT
public:
	explicit LoadFileTreeInThreadPool(const QString& path, QTreeWidget* widget, QObject* parent = nullptr)
		:QObject(parent), isQuitRequested(NOERROR), m_path(path), treeWidget(widget)
	{
		this->QRunnable::setAutoDelete(true);
	}
public:
	bool isQuitRequested;
protected:
	virtual void run() override;
signals:
	void workDone(QTreeWidget* widget);
private:
	void loadFiles(const QString& path, QTreeWidget* widget, QTreeWidgetItem* item);
	void addIcon(const QString& fileType, QTreeWidgetItem* item);
private:
	QString m_path;
	QTreeWidget* treeWidget;
};

class LoadFilesInThreadPool :public QObject,public QRunnable
{
	Q_OBJECT
public:
	explicit LoadFilesInThreadPool(const QString& path, const int type, QObject* parent = nullptr)
		:QObject(parent),m_path(path),m_type(type)
	{
		this->QRunnable::setAutoDelete(true);
	}
public:
	virtual void run() override;
signals:
	void openJson(QJsonObject json);
	void workDone(QList<QList<QVariant> > dataList);
private:
	void loadFiles(const QString& filePath, const int type);

private:
	int m_type;
	QString m_path;
};


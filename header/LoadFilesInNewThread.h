#pragma once
#include <qobject.h>
#include <QTreeWidget>
#include <qobject.h>
#include <QThread>
#include <qrunnable.h>
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
	Map = 5,
	KLine = 6,
	Radar = 7,
	BoxPlot = 8,
	HeatMap = 9,
	Relation = 10,
	Tree = 11,
	RectangleTree = 12,
	Sun = 13,
	ParallelCoordinateSystem = 14,
	Sankey = 15,
	Funnel = 16,
	DashBoard = 17,
	River = 18,
	Calendar = 19,
	Dataset = 20,
	D3Bar = 21,
	D3Scatter = 22,
	D3Surface = 23,
	D3Line = 24
};

class LoadFileTreeInNewThread: public QObject,public QRunnable
{
	Q_OBJECT
public:
	explicit LoadFileTreeInNewThread(const QString& path, QTreeWidget* widget, QObject* parent = nullptr)
		:QObject(parent), isQuitRequested(NOERROR), m_path(path), treeWidget(widget)
	{
		this->QRunnable::setAutoDelete(true);
		//QObject::connect(this, &QThread::finished, this, &QObject::deleteLater);
	}
	~LoadFileTreeInNewThread();
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

class LoadFilesInNewThread :public QObject,public QRunnable
{
	Q_OBJECT
public:
	explicit LoadFilesInNewThread(const QString& path, const int type, QObject* parent = nullptr)
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


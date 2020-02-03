#pragma once
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QtCore>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QAction>
#include <QFileDialog>
#include <QColorDialog>
#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include <QStyle>
#include "commandline.h"
#include "GeneratedFiles/ui_openchart.h"
#include "filestream.h"
#include "filedataprocess.h"
#include "Setting.h"
#include "TitleBar.h"
#include "ToolBar.h"
#include "FileModelView.h"
#include "WebViewInNewThread.h"

const QMap<QString,int> chartTypeMap = { {"line",0},{"bar",1},{"pie",2},{"scatter",3},{"flow",4},
{"kline",5},{"radar",6},{"boxplot",7},{"heatmap",8},{"relation",9},{"tree",10},{"rectangleTree",11},
{"sun",12},{"parallel",13},{"sankey",14},{"funnel",15},{"polar",16},{"river",17},{"calendar",18},
{"dataset",19},{"3dbar",20},{"3dscatter",21},{"3dsurface",22},{"3dmap",23},{"3dline",24} };
class OpenChartPrivate;
class OPENCHART : public QMainWindow
{
	Q_OBJECT
public:
	OPENCHART(QWidget* parent = Q_NULLPTR);

public slots:
	void connected();
private:
	void createConnections();
	void openJson(const QString& filePath);
	void basicPlot(const QString& chartType);
	void jsonFromInit(const QJsonObject& json);
	void feedFileDataToJson(QList<QList<QVariant> > dataList);
	void createMenuBar();
	void createStatusBar();
	void reloadChart(const QString& str);
	void initPropertyTreeWidget();
	void addWidgetToTreeWidget(QTreeWidgetItem* item, const int column, QWidget* widget);
	void addComboBox(QTreeWidgetItem* item);
	void addLineEdit(QTreeWidgetItem* item);
	void addColorPicker(QTreeWidgetItem* item);
	void addFontPicker(QTreeWidgetItem* item);
public slots:
	void openFile();
	void saveFile();

	void plotSlot(const QString& name);
	void chartThemeChangeSlot(const QString& theme);
	void optionChangedSlot();
	void initChart(QTreeWidgetItem* item, int column);
	void updateStatusBar();
	void setChartTypeDockWidgetVisable();
	void setCommandLineDockWidgetvisable();
	void setOptionDockWidgetVisable();
	void setFileViewDockWidgetVisable();
	void isFileViewWidgetVisable(bool visable)
	{
		emit isWidgetVisableSignal(ResourceManager, visable);
	}
	void isChartTypeWidgetVisable(bool visable)
	{
		emit isWidgetVisableSignal(ChartTypeMenuAction, visable);
	}
	void isProertyWidgetVisable(bool visable)
	{
		emit isWidgetVisableSignal(PropertyMenuAction, visable);
	}
	void isCommandLineVisable(bool visable)
	{
		emit isWidgetVisableSignal(CommandLineMenuAction, visable);
	}
//toolBar slots
public slots:
	void titleBarOpenFolderActionTriggered();
	void toolBarResourceButtonClickedSlot();
	void toolBarSearchButtonClickedSlot();
	void toolBarChoseChartTypeButtonClickedSolt();
	void toolBarEditOptionButtonClickedSlot();
	void toolBarSettingButtonClickedSlot();
signals:
	void isWidgetVisableSignal(const int index, bool visable);
	void nowChartTheme(const QString& themeName);
	void loadFileInNewThreadSignal(const QString& path,const int type);
	void webViewLoad(QUrl url);
signals:
	void sendMsgSignal(const QString& msg);
	void jsErrorSignal(const int error);
signals:
	void chartShowLoadingSignal();
signals:
	void updateStatusBarSignal();
private slots:
	//when opened file is a json file, call this spacial function
	void jsonFromUser(const QJsonObject& json);
	//set theme for chart.webview will load a new h5 page
	void setChartTheme(const QString& themeName);
	//this function emits a signal which connects to the actual file load function.
	void loadFileByName(const QString& fileName);
private:
	Ui::OPENCHART ui;
	bool isOptionChanged;
	bool isUserInput;
	//bool isFileSaved;
	OpenChartPrivate* d_ptr;
	CommandLine* commandLine;
	ToolBar* toolBar;
	FileModelView* fileView;
	WebViewInNewThread* webView;
};



#pragma execution_character_set("utf-8")	//set char-set to utf-8
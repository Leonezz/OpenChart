#pragma once
#include <qdockwidget.h>
#include <QFileSystemModel>
#include <QtConcurrent/QtConcurrent>
#include <QTreeWidget>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QThread>
#include "LoadFilesInThreadPool.h"
#include "LoadingWidget.h"
class FileModelView :public QDockWidget
{
	Q_OBJECT
public:
	explicit FileModelView(QWidget* parent = nullptr);
	~FileModelView();
signals:
	//signal sent when item are double clicked, slots get fileName of item double clicked.
	//signal will send to OPENCHART class and send back to make sure only one way to trigger the file open in new thread action.
	void fileItemDoubleClicked(const QString& filePath);
	void sendFileDataSignal(QList<QList<QVariant> > dataList);
	void sendJsonDataSignal(QJsonObject json);
public slots:
	//slot and interface to make a file tree view.
	void buildFileTree();
	void loadFile(const QString& path,const int type);
protected:
	virtual void closeEvent(QCloseEvent* event);
private slots:
	void itemDoubleClickedSolt(QTreeWidgetItem* item, const int column);
	void setFolderExpandIcon(QTreeWidgetItem* item);
	void setFolderCollapseIcon(QTreeWidgetItem* item);
	//receive result from newThread.
	void receiveFileTree(QTreeWidget* widget);
	//stop worker process and the thread the process is in.
	void terminateFileTreeLoadProcess();
private:
	void getFolderPath();
	void createFileTreeLoader(const QString& path,QTreeWidget* widget);
private:
	//make sure all these pointers are initialized
	QString m_path;
	QPushButton* button;
	QTreeWidget* treeView;
	LoadFilesInThreadPool* fileLoader;
	LoadFileTreeInThreadPool* fileTreeLoader;
	LoadingWidget* loading;
	bool isFileTreeLoaderCreated;
};
#pragma execution_character_set("utf-8")	//set char-set to utf-8

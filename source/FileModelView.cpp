
#include "header/FileModelView.h"
#include "..\header\FileModelView.h"
#include "header/JsonObject.h"
#include "QGridLayout"
FileModelView::FileModelView(QWidget* parent)
	:QDockWidget(parent), isFileTreeLoaderCreated(false)
{
	//this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowTitle(tr("资源管理器"));
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	button = new QPushButton(tr("打开文件夹"), this);
	button->setObjectName("OpenFolder");

	this->setWidget(button);

	QObject::connect(button, &QPushButton::clicked, this, &FileModelView::buildFileTree);
	this->setObjectName("FileView");

	treeView = new QTreeWidget();
	QObject::connect(treeView, &QTreeWidget::itemExpanded, this, &FileModelView::setFolderExpandIcon);
	QObject::connect(treeView, &QTreeWidget::itemCollapsed, this, &FileModelView::setFolderCollapseIcon);
	QObject::connect(treeView, &QTreeWidget::itemDoubleClicked, this, &FileModelView::itemDoubleClickedSolt);
}

void FileModelView::buildFileTree()
{
	getFolderPath();
	if (m_path.isEmpty())
	{
		return;
	}

	if (isFileTreeLoaderCreated)
	{	//already loading
		terminateFileTreeLoadProcess();
		while (isFileTreeLoaderCreated) {
			QApplication::processEvents();
		}
	}

	button->close();
	loading = new LoadingWidget(this);
	loading->setObjectName("Loading");

	this->setWidget(loading);
	this->setWindowTitle("Loading...");

	treeView->clear();
	createFileTreeLoader(m_path, treeView);
}

void FileModelView::createFileTreeLoader(const QString& path, QTreeWidget* widget)
{
	fileTreeLoader = new LoadFileTreeInThreadPool(path, widget);
	isFileTreeLoaderCreated = true;
	fileTreeLoader->isQuitRequested = false;
	QObject::connect(fileTreeLoader, &LoadFileTreeInThreadPool::workDone, this, &FileModelView::receiveFileTree);
	//start file loading process in globe thread pool

	QThreadPool::globalInstance()->start(fileTreeLoader);
}

FileModelView::~FileModelView()
{
	terminateFileTreeLoadProcess();
}

void FileModelView::loadFile(const QString& path, const int type)
{
	fileLoader = new LoadFilesInThreadPool(path, type);
	QObject::connect(fileLoader, &LoadFilesInThreadPool::workDone, this, &FileModelView::sendFileDataSignal);
	QObject::connect(fileLoader, &LoadFilesInThreadPool::openJson, this, &FileModelView::sendJsonDataSignal);
	//start file loading process in globe thread pool
	QThreadPool::globalInstance()->start(fileLoader);
}

void FileModelView::receiveFileTree(QTreeWidget* widget)
{
	//treeView = widget;//this statement init treeView

	terminateFileTreeLoadProcess();

	QString folderName = m_path.split("/").last();
	const QString title = fileTreeLoader->isQuitRequested ? tr("资源管理器") + "   -   " + folderName + "(Incomplete)" :
		tr("资源管理器") + "   -   " + folderName;
	this->setWindowTitle(title);
	if (loading) {
		loading->close();
	}
	this->setWidget(treeView);
	treeView->show();
	treeView->headerItem()->setIcon(0, QIcon("./Resources/icon/fileIcons/default_root_folder_opened.svg"));
	treeView->headerItem()->setText(0, folderName);

	isFileTreeLoaderCreated = false;
}



void FileModelView::closeEvent(QCloseEvent* event)
{
	//when user want to terminate the fileLoading process in the newThread,close this window.
	terminateFileTreeLoadProcess();
	QDockWidget::closeEvent(event);
}

void FileModelView::itemDoubleClickedSolt(QTreeWidgetItem* item, const int column)
{
	Q_UNUSED(column);
	int a = 0;
	//get path of item double clicked.
	if (item->childCount() == 0)
	{
		QString filePath = m_path;
		QList<QTreeWidgetItem*> parentList;
		parentList.push_front(item);
		QTreeWidgetItem* parent = item->parent();
		while (parent)
		{
			parentList.push_front(parent);
			parent = parent->parent();
		}
		for each (auto var in parentList)
		{
			filePath += "/" + var->text(0);
		}
		emit fileItemDoubleClicked(filePath);
	}
}

void FileModelView::setFolderExpandIcon(QTreeWidgetItem* item)
{
	item->setIcon(0, QIcon("./Resources/icon/fileIcons/file_type_folder_open.svg"));
}

void FileModelView::setFolderCollapseIcon(QTreeWidgetItem* item)
{
	item->setIcon(0, QIcon("./Resources/icon/fileIcons/file_type_folder.svg"));
}


void FileModelView::terminateFileTreeLoadProcess()
{
	if (isFileTreeLoaderCreated)
	{
		fileTreeLoader->isQuitRequested = true;
	}
}

void FileModelView::getFolderPath()
{
	QFileDialog* fileDialog = new QFileDialog(this);
	fileDialog->setFileMode(QFileDialog::Directory);
	m_path = fileDialog->getExistingDirectory();
}
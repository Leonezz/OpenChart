#include "header/LoadFilesInThreadPool.h"
#include "header/filestream.h"
#include "header/filedataprocess.h"
#include <QDir>
/*--------------LoadFileTreeInNewThread-------------------*/

void LoadFileTreeInThreadPool::run()
{
	loadFiles(m_path, treeWidget, treeWidget->headerItem());
	emit workDone(treeWidget);
}

void LoadFileTreeInThreadPool::loadFiles(const QString& path, QTreeWidget* widget, QTreeWidgetItem* item)
{
	if (isQuitRequested)
	{
		return;
	}
	QDir dir(path);
	if (!dir.exists())
	{
		return;
	}
	dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks);
	const QFileInfoList fileInfoList = dir.entryInfoList();
	for (std::size_t i = 0; i < fileInfoList.length(); ++i)
	{
		const QFileInfo fileInfo = fileInfoList.at(i);
		if (fileInfo.fileName() == "." || fileInfo.fileName() == "..")
			continue;
		if (fileInfo.isDir())
		{
			QTreeWidgetItem* fileItem = new QTreeWidgetItem(QStringList() << fileInfo.fileName(), 0);
			if (widget == NULL)
			{
				item->addChild(fileItem);
			}
			else
			{
				widget->addTopLevelItem(fileItem);
			}
			addIcon("folder", fileItem);
			loadFiles(fileInfo.filePath(), NULL, fileItem);
		}
		else
		{
			QString fileType = "txt";
			const QString fileName = fileInfo.fileName();
			fileType = fileName.split(".").last();
			QTreeWidgetItem* fileItem = new QTreeWidgetItem(QStringList() << fileName, 1);
			if (widget == NULL)
			{
				item->addChild(fileItem);
			}
			else
			{
				widget->addTopLevelItem(fileItem);
			}
			addIcon(fileType, fileItem);
		}
	}
}


void LoadFileTreeInThreadPool::addIcon(const QString& fileType, QTreeWidgetItem* item)
{
	QString fileIconPath;
	QJsonObject fileIconPaths;
	if (FileStream::readJson("./Resources/settings/fileIconsPath.json", &fileIconPaths))
	{
		fileIconPath = fileIconPaths.value(fileType).toString();
		if (fileIconPath.isEmpty())
		{
			fileIconPath = "./Resources/icon/fileIcons/default_file.svg";
		}
		item->setIcon(0, QIcon(fileIconPath));
	}
	else
	{
		qDebug() << "Error opening fileIconsPath json";
	}
	

}


/*--------------LoadFilesInNewThread-------------------*/
/*
void LoadFilesInNewThread::startLoadingSlot(const QString& filePath,const int type)
{
	m_path = filePath;
	m_type = type;
}
*/


void LoadFilesInThreadPool::run()
{
	loadFiles(m_path, m_type);
}

void LoadFilesInThreadPool::loadFiles(const QString& filePath,const int type)
{
	bool fileError = false;
	QString fileType;
	fileType = filePath.split('.').last();
	QList<QList<QVariant> > dataList;
	switch (m_type)
	{
	case 1:
		fileError = FileStream::readExcel(filePath, &dataList);
		break;
	case 2:
		dataList = FileStream::readCsv(filePath);
		break;
	case 3:
		dataList = FileStream::readTxt(filePath);
		break;
	case 4:
	{
		QJsonObject json;
		if (FileStream::readJson(filePath, &json))
		{
			emit openJson(json);
		}
	}
	break;
	default:
		break;
	}
	if (fileError == NOERROR)
	{
		emit workDone(dataList);
	}
}



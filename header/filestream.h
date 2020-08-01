#pragma once
#include <QtCore>
#include <QString>
#include <QFile>
#include <QVariant>
#include <ActiveQt/QAxObject>

namespace FileStream
{
	bool readExcel(const QString& filepath, QList<QList<QVariant> >* dataList)
	{
		bool fileError = false;
		if (!filepath.isEmpty())
		{
			QAxObject* excel=new QAxObject();	//
			excel->setControl("Excel.Application");
			excel->setProperty("Visible", false);	//set excel interface hiden
			QAxObject* workBooks = excel->querySubObject("WorkBooks");	//get workbooks
			QAxObject* workBook = workBooks->querySubObject("Open(QString,QVariant)", filepath);	//get workbook by file path
			QAxObject* workSheet = workBook->querySubObject("WorkSheets(int)", 1);		//get sheet1 of current workbook
			QAxObject* usedRange = workSheet->querySubObject("UsedRange");	//get the used range of current sheet
			if (NULL != usedRange && !usedRange->isNull())
			{
				QAxObject* rows = usedRange->querySubObject("Rows");
				int firstRowIndex = rows->property("Row").toInt();		//get first row index
				int rowsAmount = rows->property("Count").toInt();	//get rows number

				QAxObject* cols = usedRange->querySubObject("Columns");
				int firstColIndex = cols->property("Column").toInt();	//get first column index
				int colsAmount = cols->property("Count").toInt();	//get columns number

				auto range = [=](int rows, int cols, int rowIndex, int colIndex) {
					auto covert26 = [=](int n) {
						QString s;
						while (n > 0) {
							int m = n % 26;
							if (m == 0)
							{
								m = 26;
							}
							s = (char)(m + 64) + s;
							n = (n - m) / 26;
						}
						return s;
					};
					QString startcol = covert26(colIndex);
					QString endcol = covert26(cols + colIndex - 1);
					QString startrow = QString::number(rowIndex);
					QString endrow = QString::number(rows + rowIndex - 1);
					return (startcol + startrow + ":" + endcol + endrow);
				}(rowsAmount, colsAmount, firstRowIndex, firstColIndex);

				//qDebug() << range;
				QAxObject* colCells;
				QAxObject* allCells = workSheet->querySubObject("Range(QString)", range);	//get cells of current range
				QVariant allDataVariant = allCells->property("Value");	//get values of all the cells
				QList<QVariant> rowList = allDataVariant.toList();	//make row value a list
				//QList<QList<QVariant> > dataList;

				QList<QVariant>::const_iterator it = rowList.constBegin();
				for (; it != rowList.constEnd(); ++it)
				{
					(*dataList).append((*it).toList());
				}

				workBooks->dynamicCall("Close(Boolean)", false);
				excel->dynamicCall("Quit(void)");

				//delete by hand
				delete allCells;
				delete cols;
				delete rows;
				delete usedRange;
				delete workSheet;
				delete workBook;
				delete workBooks;
				delete excel;
				fileError = true;
			}
		}
		return fileError;
	}
	QJsonObject readJson(const QString& filepath)
	{
		QFile jsonFile(filepath);
		if (!jsonFile.open(QIODevice::ReadOnly))
		{
			qDebug() << "can't open file.";
			//return;
		}
		QByteArray fileData = jsonFile.readAll();
		jsonFile.close();

		QJsonParseError json_error;
		QJsonDocument jsonDoc(QJsonDocument::fromJson(fileData, &json_error));

		if (json_error.error != QJsonParseError::NoError)
		{
			qDebug() << "json Error.";
			qDebug() << "Source: filestream.h :Line:105";
		}

		QJsonObject jsonObj = jsonDoc.object();
		return jsonObj;
	}

	bool readJson(const QString& filepath, QJsonObject* jsonObj)
	{
		bool fileError = true;
		bool jsonError = true;

		QFile jsonFile(filepath);
		if (!jsonFile.open(QIODevice::ReadOnly))
		{
			qDebug() << "can't open file.";
			fileError = false;
		}
		QByteArray fileData = jsonFile.readAll();
		jsonFile.close();

		QJsonParseError json_error;
		QJsonDocument jsonDoc(QJsonDocument::fromJson(fileData, &json_error));
		if (json_error.error != QJsonParseError::NoError)
		{
			qDebug() << "json Error.";
			qDebug() << "Source: filestream.h :Line:105";
			jsonError = false;
		}

		*jsonObj = jsonDoc.object();
		return fileError && jsonError;
	}

	QList<QList<QVariant>> readCsv(const QString& filepath)
	{
		return QList<QList<QVariant>>();
	}

	QList<QList<QVariant>> readTxt(const QString& filepath)
	{
		return QList<QList<QVariant>>();
	}

	void writeFile(const QString& fileName)
	{
	}
	
}

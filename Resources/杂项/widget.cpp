
#include "widget.h"

//my resources folder path.
const QString htmlFileFolderPath = "/Resources/html/";
const QString jsFileFolderPath = "/Resources/js/";
const QString jsonFileFolderPath = "/Resources/json/";


OpenChart_demo::OpenChart_demo(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	basicPlot("basic");
}

void Widget::reloadChart(QTreeWidgetItem* item, int column)
{
	//ChartType type;
	QString str = item->text(1);
	QJsonObject option = readJSON(str);
	QString msg = jsonToString(option);
	//const QString msg=array;
	//here get data.
	if (msg.isEmpty())
	{
		return;
	}

	emit sendMsg(msg);
}


void Widget::basicPlot(const QString& chartType)
{
	QUrl basicPage = QUrl::fromLocalFile(htmlFileFolderPath +chartType+".html");
	ui.myWebView->load(basicPage);
}

void Widget::displayData()
{
	//do something.
}



void Widget::clicked()
{
	//QJsonObject option = makeData();
	//QJsonDocument doc;
	//doc.setObject(option);
	QString str;
	QJsonObject option = readJSON(str);
	QString msg=jsonToString(option);
	//const QString msg=array;
	//here get data.

	if (msg.isEmpty())
	{
		return;
	}

	emit sendMsg(msg);

}

QJsonObject OpenChart_demo::makeData(const QJsonObject& objFromFile)
{
	QJsonObject option=readJSON("line");
	QJsonObject series;

	QJsonArray seriesArray = objFromFile.value("series").toArray();
	for (int i = 0; i < seriesArray.size(); ++i)
	{
		QJsonObject o = seriesArray[i].toObject();
		o.insert("type", "line");
		seriesArray[i] = o;
	}
	option.insert("series", seriesArray);
	QJsonArray xAxis = objFromFile.value("xAxis").toArray();
	QJsonObject x;
	x.insert("data", xAxis);

	option.insert("xAxis", x);
	//QJsonArray data = series.value("data").toArray();
	QString str=jsonToString(option);
	qDebug() << str;
	emit sendMsg(str);
	return option;
}

QJsonObject OpenChart_demo::readJSON(const QString& name)
{
	QFile jsonFile("."+jsonFileFolderPath + name+".json");
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
		//return;
	}

	QJsonObject jsonObj = jsonDoc.object();
	return jsonObj;
}

QString OpenChart_demo::jsonToString(const QJsonObject& jsonObj)
{
	QJsonDocument doc;
	doc.setObject(jsonObj);
	QString str(doc.toJson(QJsonDocument::Compact));
	return str;
}

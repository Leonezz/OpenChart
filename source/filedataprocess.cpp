/*
	Authur: zhu wenqiang

	This file is the implementation file of the functional namespace DataProcess 
	where the core data process functions are declared.

	all kinds of chart get its json data changed here.
*/

#include "header/filedataprocess.h"
#include "header/optionindexfile.h"
#include <QMetaType>

Q_DECLARE_METATYPE(QList<QList<QVariant> >);

namespace DataProcess
{
	void dataForLine(const QList<QList<QVariant> >& dataList,JsonObject* json)
	{
		//if x & y is the header,plot value line.
		auto valueType = [&](const QList<QList<QVariant> >& dataList, JsonObject* json) {
			QJsonArray seriesArr;
			QJsonObject seriesItem;
			seriesItem.insert("type", "line");
			seriesArr.append(seriesItem);
			(*json).replace(OptionIdentity::option::series, seriesArr);
			(*json).replace(OptionIdentity::xAxis::type, QString("value"));
			dataForScatter(dataList, json);
		};
		//if series names is the header,plot normal lines
		auto stringType = [&](const QList<QList<QVariant> >& dataList, JsonObject* json) {
			auto covertVariantToJsonValue = [&](const QVariant& variant, QJsonValue* value, bool* isFloat) {
				const float floatVal = variant.toFloat(isFloat);
				if (*isFloat) {
					*value = QJsonValue(floatVal);
				}
				else {
					*value = QJsonValue(variant.toString());
				}
			};
			
			QJsonArray seriesArr;
			QJsonArray legendDataArr;
			bool isXFloat = false;
			const int colsCount = dataList[0].length();
			const int rowsCount = dataList.length();
			QJsonObject seriesItem = (*json).get().value("series").toArray()[0].toObject();
			for (sizetype i = 1; i < colsCount; ++i)
			{
				QJsonArray seriesDataItem;
				for (sizetype j = 1; j < rowsCount; ++j)
				{
					seriesDataItem.append(dataList[j][i].toFloat());
				}
				seriesItem.insert("data", seriesDataItem);
				seriesItem.insert("name", dataList[0][i].toString());
				legendDataArr.append(dataList[0][i].toString());
				seriesArr.append(seriesItem);
			}
			QJsonArray xAxisDataArr;
			for (sizetype i = 1; i < rowsCount; ++i)
			{
				xAxisDataArr.append(dataList[i][0].toString());
			}
			json->replace(OptionIdentity::xAxis::data, xAxisDataArr);
			json->replace(OptionIdentity::legend::data, legendDataArr);
			json->replace(OptionIdentity::option::series, seriesArr);
			emit json->valueChanged();
		};

		const QList<QVariant>& header = dataList[0];
		bool isValueType = false;
		bool x = false;
		bool y = false;
		for (sizetype i = 0; i < header.length(); ++i)
		{
			if (header[i].toString() == "x") {
				x = true;
			}//else do nothing
			if (header[i].toString() == "y") {
				y = true;
			}//else do nothing
			isValueType = x && y;
			if (isValueType) {
				break;
			}
		}
		
		if (isValueType) {
			valueType(dataList, json);
		}
		else {
			stringType(dataList, json);
		}
	}

	void dataForBar(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		dataForLine(dataList, json);
	}

	void dataForPie(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		//QJsonObject series = (*json).get().value("series").toArray().first().toObject();
		QJsonArray dataArr;
		QJsonArray legendDataArr;
		for each (auto var in dataList)
		{
			QJsonObject dataObj;
			const QString& name = var.first().toString();
			dataObj.insert("name", name);
			legendDataArr.append(name);
			dataObj.insert("value", var.last().toFloat());
			dataArr.append(dataObj);
		}
		json->replace(OptionIdentity::legend::data, legendDataArr);
		json->replace(OptionIdentity::series::data, dataArr);
		emit json->valueChanged();
	}

	void dataForScatter(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		const QList<QVariant>& header = dataList[0];
		const int headerCols = header.length();
		const QMap<QString, sizetype> indexMap = {
			{"x",0},{"y",1}
		};
		sizetype indexs[2] = { 0,0 };
		for (sizetype i = 0; i < headerCols; ++i)
		{
			const QString& str = header[i].toString();
			QMap<QString, sizetype>::const_iterator iter = indexMap.find(str);
			if (iter != indexMap.end()) {
				indexs[iter.value()] = i;
			}
			else {
				//Error
			}
		}

		const sizetype xIndex = indexs[0];
		const sizetype yIndex = indexs[1];

		const int rows = dataList.length();
		//QSet<QJsonValue> xAxisDataSet;
		//QSet<QJsonValue> yAxisDataSet;
		QJsonArray data;
		auto covertVariantToJsonValue = [&](const QVariant& variant, QJsonValue* value) {
			bool isFloat = false;
			const float floatVal = variant.toFloat(&isFloat);
			if (isFloat) {
				*value = QJsonValue(floatVal);
			}
			else {
				*value = QJsonValue(variant.toString());
			}
		};
		for (sizetype i = 1; i < rows; ++i)
		{
			const QList<QVariant>& rowList = dataList[i];
			QJsonArray dataItem;
			QJsonValue value;
			covertVariantToJsonValue(rowList[xIndex], &value);
			dataItem.append(value);
			//xAxisDataSet.insert(value);
			
			covertVariantToJsonValue(rowList[yIndex], &value);
			dataItem.append(value);
			//yAxisDataSet.insert(value);

			data.append(dataItem);
		}
		/*auto lessThen = [&](const QJsonValue& f, const QJsonValue& h) {
			if (f.isString() || h.isString()) {
				return true;
			}
			else {
				return f.toDouble() < h.toDouble();
			}
		};*/
		//QList<QJsonValue> xAxisDataList = xAxisDataSet.toList();
		//qSort(xAxisDataList.begin(), xAxisDataList.end(), lessThen);

		//QList<QJsonValue> yAxisDataList = yAxisDataSet.toList();
		//qSort(yAxisDataList.begin(), yAxisDataList.end(), lessThen);

		//QJsonArray xAxisDataArr;
		//QJsonArray yAxisDataArr;
		//for (sizetype i = 0; i < xAxisDataList.length(); ++i)
		//{
		//	xAxisDataArr.append(xAxisDataList[i]);
		//	//yAxisDataArr.append(yAxisDataList[i]);
		//}

		json->replace(OptionIdentity::series::data, data);
		//(*json).replace(OptionIdentity::xAxis::data, xAxisDataArr);
		//(*json).replace(OptionIdentity::yAxis::data, yAxisDataArr);
		emit json->valueChanged();
	}

	void dataForFlow(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		QJsonArray dataArr;
		const int rows = dataList.length();
		for (sizetype i = 0; i < rows; ++i)
		{
			QJsonArray dataItem;
			const QList<QVariant>& rowList = dataList[i];
			const int cols = rowList.length();
			for (sizetype j = 0; j < cols; ++j)
			{
				dataItem.append(rowList[j].toFloat());
			}
			dataArr.append(dataItem);
		}
		json->replace(OptionIdentity::series::data, dataArr);
		emit json->valueChanged();
	}

	void dataForKLine(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		const QList<QVariant>& header = dataList[0];
		const int headerCols = header.length();
		const QMap<QString, sizetype> indexMap = {
		{"date",0},{"code",1},{"open",2},{"high",3},{"low",4},{"close",5}
		};
		sizetype indexs[6] = { 0,0,0,0,0,0 };
		for (sizetype i = 0; i < headerCols; ++i)
		{
			const QString& str = header[i].toString();
			QMap<QString, sizetype>::const_iterator iter = indexMap.find(str);
			if (iter != indexMap.end()) {
				indexs[iter.value()]= i;
			}
			else {
				//Error
			}
		}
		const int rows = dataList.length();
		const sizetype dateIndex = indexs[0];
		const sizetype  codeIndex = indexs[1];
		const sizetype  openIndex = indexs[2];
		const sizetype  highIndex = indexs[3];
		const sizetype  lowIndex = indexs[4];
		const sizetype  closeIndex = indexs[5];
		QJsonArray xAxisDataArr;
		QJsonArray seriesDataArr;
		for (sizetype i = 0; i < rows; ++i)
		{
			const QList<QVariant>& rowList = dataList[i];
			xAxisDataArr.append(rowList[dateIndex].toString());
			QJsonArray seriesDataItem;
			seriesDataItem.append(rowList[openIndex].toFloat());
			seriesDataItem.append(rowList[highIndex].toFloat());
			seriesDataItem.append(rowList[lowIndex].toFloat());
			seriesDataItem.append(rowList[closeIndex].toFloat());
			seriesDataArr.append(seriesDataItem);
		}
		json->replace(OptionIdentity::xAxis::data, xAxisDataArr);
		json->replace(OptionIdentity::series::data, seriesDataArr);
		json->replace(OptionIdentity::series::name, dataList[1][codeIndex].toString());
		json->replace(OptionIdentity::legend::data, dataList[1][codeIndex].toString());
		emit(*json).valueChanged();
	}

	void dataForRadar(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		const int rows = dataList.length();
		QJsonArray indicatorDataArr;
		const QList<QVariant>& header = dataList[0];
		for (sizetype i = 1; i < header.length(); ++i)
		{
			QJsonObject indicatorObj;
			indicatorObj.insert("name", header[i].toString());
			indicatorDataArr.append(indicatorObj);
		}
		json->replace(OptionIdentity::radar::indicator, indicatorDataArr);

		QJsonArray seriesDataArr;
		QJsonArray legendDataArr;
		for (sizetype i = 1; i < rows; ++i)
		{
			const QList<QVariant>& rowList = dataList[i];
			const int cols = rowList.length();
			QJsonArray seriesDataValue;
			QJsonObject seriesDataItem;
			for (sizetype j = 1; j < cols; ++j)
			{
				seriesDataValue.append(rowList[j].toFloat());
			}
			seriesDataItem.insert("value", seriesDataValue);
			const QString& name = dataList[i][0].toString();
			seriesDataItem.insert("name", name);
			legendDataArr.append(name);
			seriesDataArr.append(seriesDataItem);
		}
		(*json).replace(OptionIdentity::legend::data, legendDataArr);
		(*json).replace(OptionIdentity::series::data, seriesDataArr);
		emit(*json).valueChanged();
	}

	void dataForTree(const QList<QList<QVariant>>&, JsonObject*)
	{
		
	}

	void dataForTreeMap(const QList<QList<QVariant>>&, JsonObject*)
	{
	}

	void dataForSun(const QList<QList<QVariant>>&, JsonObject*)
	{
	}

	void dataForBoxplot(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		const int rows = dataList.length();
		const int cols = dataList[0].length();

		auto getQuartile = [&](const QVector<float>& vec, const int pos) {
			int n = vec.length();
			int low = n * pos / 4;
			float decimal = (n * pos / 4) - low;
			float lowQuartile = (decimal == 0) ? vec.at(low) : (vec.at(low) + vec.at(low + 1) / 2);
			return lowQuartile;
		};

		auto getDataItem = [&](const QVector<float>& vec) {
			QJsonArray arr;
			arr.append(vec.first());
			for (unsigned int i = 1; i < 4; ++i)
			{
				arr.append(getQuartile(vec, i));
			}
			arr.append(vec.last());
			return arr;
		};

		auto lessThan = [&](const float a, const float b) {
			return a < b;//Ascending
		};

		QJsonArray seriesDataArr;
		QJsonArray xAxisDataArr;
		for (sizetype i = 1; i < cols; ++i)
		{
			xAxisDataArr.append(dataList[0][i].toString());
			QVector<float> temp;
			for (sizetype j = 1; j < rows; ++j)
			{
				temp.push_back(dataList[j][i].toFloat());
			}
			qSort(temp.begin(),temp.end(), lessThan);
			seriesDataArr.append(getDataItem(temp));
		}
		(*json).replace(OptionIdentity::xAxis::data, xAxisDataArr);
		(*json).replace(OptionIdentity::series::data, seriesDataArr);
		emit(*json).valueChanged();
	}

	void dataForHeatmap(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		QJsonArray xAxisDataArr;
		for (sizetype i = 1; i < dataList[0].length(); ++i)
		{
			xAxisDataArr.append(dataList[0][i].toFloat());
		}
		(*json).replace(OptionIdentity::xAxis::data, xAxisDataArr);

		const int rows = dataList.length();
		QJsonArray seriesDataArr;
		QJsonArray yAxisDataArr;
		for (sizetype i = 1; i < rows; ++i)
		{
			yAxisDataArr.append(dataList[i][0].toFloat());
			const QList<QVariant>& rowList = dataList[i];
			const int cols = rowList.length();
			for (sizetype j = 1; j < cols; ++j)
			{
				QJsonArray dataItem;
				dataItem.append(float(j-1));
				dataItem.append(float(i-1));
				dataItem.append(rowList[j].toFloat());
				seriesDataArr.append(dataItem);
			}
		}
		(*json).replace(OptionIdentity::series::data, seriesDataArr);
		(*json).replace(OptionIdentity::yAxis::data, yAxisDataArr);
		emit(*json).valueChanged();
	}

	void dataForParallelCoordinates(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		QJsonArray parallelAxisArr;
		for (sizetype i = 1; i < dataList[0].length(); ++i)
		{
			QJsonObject parallelAxisItem;
			parallelAxisItem.insert("dim", int(i - 1));
			parallelAxisItem.insert("name", dataList[0][i].toString());
			parallelAxisArr.append(parallelAxisItem);
		}
		(*json).replace(OptionIdentity::option::parallelAxis, parallelAxisArr);

		const int rows = dataList.length();
		QJsonArray seriesDataArr;
		for (sizetype i = 1; i < rows; ++i)
		{
			const QList<QVariant>& rowList = dataList[i];
			const int cols = rowList.length();
			QJsonObject seriesDataItem;
			seriesDataItem.insert("name", dataList[i][0].toString());
			QJsonArray seriesDataValue;
			for (sizetype j = 1; j < cols; ++j)
			{
				seriesDataValue.append(rowList[j].toString());
			}
			seriesDataItem.insert("value", seriesDataValue);
			seriesDataArr.append(seriesDataItem);
		}
		const QString& name = dataList[0][0].toString();
		(*json).replace(OptionIdentity::series::name, name);
		QJsonArray legendArr = (*json).get().value("legend").toArray()[0].toObject().value("data").toArray();
		legendArr.append(name);
		(*json).replace(OptionIdentity::legend::data, legendArr);
		(*json).replace(OptionIdentity::series::data, seriesDataArr);
		emit(*json).valueChanged();
	}

	void dataForSankey(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		const QList<QVariant>& header = dataList[0];
		const int headerCols = header.length();
		const QMap<QString, sizetype> indexMap = {
			{"source",0},{"target",1},{"value",2}
		};
		sizetype indexs[3] = { 0,0,0 };
		for (sizetype i = 0; i < headerCols; ++i)
		{
			const QString& str = header[i].toString();
			QMap<QString, sizetype>::const_iterator it = indexMap.find(str);
			if (it != indexMap.end()) {
				indexs[it.value()] = i;
			}
			else {
				//error
			}
		}
		const int rows = dataList.length();
		const sizetype sourceIndex = indexs[0];
		const sizetype targetIndex = indexs[1];
		const sizetype valueIndex = indexs[2];
		QJsonArray dataArr;
		QJsonArray linkArr;
		QSet<QString> dataRecordedSet;
		for (sizetype i = 1; i < rows; ++i)
		{
			const QList<QVariant>& rowList = dataList[i];
			const QString& sourceName = rowList[sourceIndex].toString();
			const QString& targetName = rowList[targetIndex].toString();
			QJsonObject linkItem;
			linkItem.insert("source", sourceName);
			linkItem.insert("target", targetName);
			linkItem.insert("value", rowList[valueIndex].toFloat());
			linkArr.append(linkItem);

			auto feedDataArr = [&](const QString& name, QJsonArray& arr, QSet<QString>& set) {
				QJsonObject dataItem;
				dataItem.insert("name", name);
				arr.append(dataItem);
				set.insert(name);
			};

			QSet<QString>::const_iterator isSourceItemRecorded = dataRecordedSet.find(sourceName);
			if (isSourceItemRecorded == dataRecordedSet.end()) {
				feedDataArr(sourceName, dataArr, dataRecordedSet);
			}
			QSet<QString>::const_iterator isTargetItemRecorded = dataRecordedSet.find(targetName);
			if (isTargetItemRecorded == dataRecordedSet.end())
			{
				feedDataArr(targetName, dataArr, dataRecordedSet);
			}
		}
		(*json).replace(OptionIdentity::series::links, linkArr);
		(*json).replace(OptionIdentity::series::data, dataArr);
		emit(*json).valueChanged();
	}

	void dataForRelation(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		const QList<QVariant>& header = dataList[0];
		const int headerCols = header.length();
		const QMap<QString, sizetype> indexMap = {
			{"category",0},{"source",1},{"target",2},{"value",3}
		};
		sizetype indexs[4] = { 0,0,0,0 };
		for (sizetype i = 0; i < headerCols; ++i)
		{
			const QString& str = header[i].toString();
			QMap<QString, sizetype>::const_iterator iter = indexMap.find(str);
			if (iter != indexMap.end()) {
				indexs[iter.value()] = i;
			}
			else {
				//error
			}
		}

		const sizetype categoryIndex = indexs[0];
		const sizetype sourceIndex = indexs[1];
		const sizetype targetIndex = indexs[2];
		const sizetype valueIndex = indexs[3];
		const int rows = dataList.length();
		QJsonArray dataArr;
		QJsonArray linkArr;
		QJsonArray categoryArr;
		QJsonArray legendDataArr;
		QSet<QString> dataRecordedSet;
		QSet<QString> categoryRecordedSet;
		for (sizetype i = 1; i < rows; ++i)
		{
			const QList<QVariant>& rowList = dataList[i];
			const QString& sourceName = rowList[sourceIndex].toString();
			const QString& targetName = rowList[targetIndex].toString();
			const QString& categoryName = rowList[categoryIndex].toString();
			QJsonObject linkItem;
			linkItem.insert("source", sourceName);
			linkItem.insert("target", targetName);
			linkArr.append(linkItem);
			auto feed = [&](const QString& name,const QString& category,const float value, QJsonArray& arr, QSet<QString>& set) {
				QJsonObject dataItem;
				dataItem.insert("name", name);
				dataItem.insert("value", value);
				dataItem.insert("category", category);
				arr.append(dataItem);
				set.insert(name);
			};
			QSet<QString>::const_iterator isSourceItemRecorded = dataRecordedSet.find(sourceName);
			if (isSourceItemRecorded == dataRecordedSet.end()) {
				feed(sourceName, categoryName, rowList[valueIndex].toFloat(), dataArr, dataRecordedSet);
			}
			QSet<QString>::const_iterator isTargetItemRecorded = dataRecordedSet.find(targetName);
			if (isTargetItemRecorded == dataRecordedSet.end()) {
				feed(targetName, categoryName, rowList[valueIndex].toFloat(), dataArr, dataRecordedSet);
			}
			QSet<QString>::const_iterator isCategoryItemRecorded = categoryRecordedSet.find(categoryName);
			if (isCategoryItemRecorded == categoryRecordedSet.end()) {
				legendDataArr.append(categoryName);
				QJsonObject categoryItem;
				categoryItem.insert("name", categoryName);
				categoryArr.append(categoryItem);
				categoryRecordedSet.insert(categoryName);
			}
		}
		(*json).replace(OptionIdentity::series::data, dataArr);
		(*json).replace(OptionIdentity::series::links, linkArr);
		(*json).replace(OptionIdentity::series::categories, categoryArr);
		(*json).replace(OptionIdentity::legend::data, legendDataArr);
		emit(*json).valueChanged();
		
	}

	void dataForFunnel(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		const QList<QVariant>& header = dataList[0];
		const int headerCols = header.length();
		QMap<QString, sizetype> indexMap = {
			{"name",0},{"value",1}
		};
		sizetype indexs[2] = { 0,0 };
		for (sizetype i = 0; i < headerCols; ++i)
		{
			const QString& str = header[i].toString();
			QMap<QString, sizetype>::const_iterator iter = indexMap.find(str);
			if (iter != indexMap.end()) {
				indexs[iter.value()] = i;
			}
			else {
				//error
			}
		}

		const sizetype nameIndex = indexs[0];
		const sizetype valueIndex = indexs[1];
		const int rows = dataList.length();
		QJsonArray seriesDataArr;
		QJsonArray legendDataArr;
		for (sizetype i = 1; i < rows; ++i)
		{
			QJsonObject seriesDataItem;
			const QList<QVariant>& rowList = dataList[i];
			const QString& name = rowList[nameIndex].toString();
			seriesDataItem.insert("name", name);
			seriesDataItem.insert("value", rowList[valueIndex].toFloat());
			seriesDataArr.append(seriesDataItem);
			legendDataArr.append(name);
		}
		(*json).replace(OptionIdentity::series::data, seriesDataArr);
		(*json).replace(OptionIdentity::legend::data, legendDataArr);
		emit(*json).valueChanged();
	}

	void dataForRiver(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		const int rowsCount = dataList.length();
		QJsonArray seriesDataArr;
		QJsonArray legendDataArr;
		QJsonArray singleAxisData;
		for (sizetype row = 1; row < rowsCount; ++row)
		{
			const QList<QVariant>& rowList = dataList[row];
			singleAxisData.append(rowList[0].toString());
			const int colsCount = rowList.length();
			for (sizetype col = 1; col < colsCount; ++col)
			{
				legendDataArr.append(dataList[0][col].toString());//legend/name/series
				QJsonArray seriesDataItem;
				seriesDataItem.append(rowList[0].toString());	//xAxis
				seriesDataItem.append(rowList[col].toFloat());	//value
				seriesDataItem.append(dataList[0][col].toString());//name/series
				seriesDataArr.append(seriesDataItem);
			}
		}
		(*json).replace(OptionIdentity::singleAxis::type, dataList[0][0].toString());
		(*json).replace(OptionIdentity::singleAxis::data, singleAxisData);
		(*json).replace(OptionIdentity::series::data, seriesDataArr);
		(*json).replace(OptionIdentity::legend::data, legendDataArr);
		emit(*json).valueChanged();
	}

	void dataForCalendar(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		const QList<QVariant>& header = dataList[0];
		const int headerCols = header.length();
		const QMap<QString, sizetype> indexMap = {
			{"time",0},{"value",1}
		};
		sizetype indexs[2] = { 0,0 };
		bool isDataComplete;
		headerIndex(header, indexMap, indexs, &isDataComplete);
		const sizetype timeIndex = indexs[0];
		const sizetype valueIndex = indexs[1];
		const int rowsCount = dataList.length();
		QJsonArray calendarRangeArr;
		QJsonArray seriesDataArr;
		for (sizetype i = 1; i < rowsCount; ++i)
		{
			const QList<QVariant>& rowList = dataList[i];
			calendarRangeArr.append(rowList[timeIndex].toString());
			QJsonArray seriesDataItem;
			seriesDataItem.append(rowList[timeIndex].toString());
			seriesDataItem.append(rowList[valueIndex].toString());
			seriesDataArr.append(seriesDataItem);
		}
		(*json).replace(OptionIdentity::series::data, seriesDataArr);
		(*json).replace(OptionIdentity::calender::range, calendarRangeArr);
		emit(*json).valueChanged();
	}

	void dataForDataSet(const QList<QList<QVariant>>&, JsonObject*)
	{

	}

	void dataForPolar(const QList<QList<QVariant> >& dataList, JsonObject* json)
	{
		dataForScatter(dataList, json);
	}

	void dataForScatter3D(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		QJsonArray xAxis3DDataArr;
		for (sizetype i = 1; i < dataList[0].length(); ++i)
		{
			xAxis3DDataArr.append(dataList[0][i].toFloat());
		}
		(*json).replace(OptionIdentity::xAxis3D::data, xAxis3DDataArr);

		const int rows = dataList.length();
		QJsonArray seriesDataArr;
		QJsonArray yAxis3DDataArr;
		for (sizetype i = 1; i < rows; ++i)
		{
			yAxis3DDataArr.append(dataList[i][0].toFloat());
			const QList<QVariant>& rowList = dataList[i];
			const int cols = rowList.length();
			for (sizetype j = 1; j < cols; ++j)
			{
				QJsonArray dataItem;
				dataItem.append(float(j - 1));
				dataItem.append(float(i - 1));
				dataItem.append(rowList[j].toFloat());
				seriesDataArr.append(dataItem);
			}
		}
		(*json).replace(OptionIdentity::series::data, seriesDataArr);
		(*json).replace(OptionIdentity::yAxis3D::data, yAxis3DDataArr);
		emit(*json).valueChanged();
	}

	void dataForBar3D(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{ 
		dataForScatter3D(dataList, json);
	}

	void dataForLine3D(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		dataForScatter3D(dataList, json);
	}

	void dataForSurface3D(const QList<QList<QVariant>>& dataList, JsonObject* json)
	{
		dataForScatter3D(dataList, json);
	}

	QString jsonToString(const QJsonObject& json)
	{
		QJsonDocument doc;
		doc.setObject(json);
		QString str(doc.toJson(QJsonDocument::Compact));
		return str;
	}

	inline void headerIndex(const QList<QVariant>& header, const QMap<QString, sizetype>& indexMap, 
		sizetype* indexs, bool* complete)
	{
		*complete = true;
		const int headerCols = header.length();
		for (sizetype i = 0; i < headerCols; ++i)
		{
			const QString& str = header[i].toString();
			QMap<QString, sizetype>::const_iterator iter = indexMap.find(str);
			if (iter != indexMap.end()) {
				indexs[iter.value()] = i;
			}
			else {
				*complete = false;
			}
		}
	}
}

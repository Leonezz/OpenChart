/*
Copyright (C) 2019 OpenChart
Author:wenqiang zhu
Time:8-26-2019  2:59
	This is a class derived from the QJsonObject class,which means this is a 
QJsonObject essentially.
	It stores my option json data,and I want it's child items easy to change.
	Some functions are added to the QJsonObject in this secondary packaged class 
to offer me what I want.These functions may be not elegant,but it does make my hands cleaner 
when I change the child items of this json object.
*/


#pragma once
#include "optionindexfile.h"
#include <QtCore>
#include <QJsonObject>
#include <QJSonArray>
#include <QStringList>


class JsonObject :public QObject
{
	Q_OBJECT

public:
	JsonObject() = default;
	JsonObject(QJsonObject& son);
	JsonObject& operator=(const QJsonObject& val);
	QJsonObject operator=(const JsonObject& val);
	//set interfaces to make sure only allowed types to be arguments when these functions are called.

	void set(const int identity, const QString& str, const std::size_t index);
	template<typename T>
	inline void replace(const int identity, const T& source, const std::size_t index = 0);
	void resizeParent(const int identity, const std::size_t size);
	void clear(const int identity, const std::size_t index);
	const int dataType(const int id);

	//get interface to copy data out.
	QJsonObject get()const;
	void get(const int identity, const QString& index, QJsonValue* value);
signals:
	void valueChanged();
private:
	QJsonObject mainObject;
	//inline functions do basic work.
	inline const QString primaryItem(const int identity);
	inline const QString secondaryItem(const int identity);
	QJsonArray arrFromString(const QString& str);
	bool isParent(const int identity);


private:
	enum DataType
	{
		String = 1,
		Number = 2,
		Boolean = 3,
		Array = 4,
		Object = 5,
		NumberOrString = 6,
		NumberOrArray = 7,
		StringOrBoolean = 8,
		BooleanOrArray = 9
	};
};



#include "header/JsonObject.h"

JsonObject& JsonObject::operator=(const QJsonObject& val)
{
	mainObject = val;
	emit valueChanged();
	return *this;
}

QJsonObject JsonObject::operator=(const JsonObject& val)
{
	return mainObject;
}

void JsonObject::set(const int identity, const QString& str, const std::size_t index)
{
	bool ok;
	int value;
	switch (dataType(identity))
	{
	case DataType::String:
		replace<QString>(identity, str, index);
		break;
	case DataType::Number:
		value = str.toInt(&ok);
		if (ok)
		{
			replace<int>(identity, value, index);
		}
		break;
	case DataType::Boolean:
		if (str == "true")
		{
			replace<bool>(identity, true, index);
		}
		else if (str == "false")
		{
			replace<bool>(identity,false,index);
		}
		break;
	case DataType::Array:
		replace<QJsonArray>(identity, arrFromString(str), index);
		break;
	case DataType::Object:
		break;
	case DataType::NumberOrString:
		value = str.toInt(&ok);
		if (ok)
		{
			replace<int>(identity, value, index);
		}
		else
		{
			replace<QString>(identity, str, index);
		}
		break;
	case DataType::NumberOrArray:
		value = str.toInt(&ok);
		if (ok)
		{
			replace<int>(identity, value, index);
		}
		else
		{
			replace<QJsonArray>(identity, arrFromString(str), index);
		}
		break;
	case DataType::StringOrBoolean:
		if (str == "true")
		{
			replace<bool>(identity, true, index);
		}
		else if (str == "false")
		{
			replace<bool>(identity, false, index);
		}
		else
		{
			replace<QString>(identity, str, index);
		}
		break;
	case DataType::BooleanOrArray:
		if (str == "true")
		{
			replace<bool>(identity, true, index);
		}
		else if (str == "false")
		{
			replace<bool>(identity, false, index);
		}
		else
		{
			replace<QJsonArray>(identity, arrFromString(str), index);
		}
		break;
	default:
		break;
	}
	emit valueChanged();
}

void JsonObject::resizeParent(const int identity, const std::size_t size)
{
	const QString parent = primaryItem(identity);
	QJsonArray arr = mainObject.value(parent).toArray();
	if (arr.size() > size)
	{
		if (isParent(identity))
		{
			for (std::size_t index = size - 1; index < arr.size(); ++index)
			{
				arr.removeAt(index);
			}
			mainObject.insert(parent, arr);
		}
	}
}

void JsonObject::clear(const int identity, const std::size_t index)
{
	const QString parent = primaryItem(identity);
	QJsonArray arr = mainObject.value(parent).toArray();
	if (arr.size() > index)
	{
		if (isParent(identity))
		{
			arr.removeAt(index);
			mainObject.insert(parent, arr);
		}
		else
		{
			const QString child = secondaryItem(identity);
			QJsonObject obj = arr.at(index).toObject();
			obj.remove(child);
			arr[index] = obj;
			mainObject.insert(parent, arr);
		}
	}
	emit valueChanged();
}

const int JsonObject::dataType(const int id)
{
	return id/10000;
}

QJsonObject JsonObject::get() const
{
	return mainObject;
}

void JsonObject::get(const int identity, const QString& index, QJsonValue* value)
{
	const QString& parent = primaryItem(identity);
	const QJsonArray& arr = mainObject.value(parent).toArray();
	//QJsonValue result = QJsonValue();
	if (isParent(identity))
	{
		*value = QJsonValue(arr);
		bool ok;
		int index_value = index.toInt(&ok);
		if (ok)
		{
			if (arr.size() > index_value)
			{
				*value = arr.at(index_value);
			}
		}
	}
	else
	{
		const QString child = secondaryItem(identity);
		QJsonArray temp;
		
		for (int i = 0; i < arr.size(); ++i)
		{
			temp.append(arr[i].toObject().value(child));
		}
		*value = temp;
		bool ok;
		int index_value = index.toInt(&ok);
		if (ok)
		{
			if (arr.size() > index_value)
			{
				*value = arr[index_value].toObject().value(child);
			}

		}
	}
}

inline const QString JsonObject::primaryItem(const int identity)
{
	const std::size_t index = isParent(identity) ? (identity % 10000 - 1451) : 
		((identity % 10000) / 50);
	QString primaryItemName = QString();
	if (index < OptionIdentity::PrimaryItemArray.length())
	{
		primaryItemName = OptionIdentity::PrimaryItemArray.at(index);
	}
	return primaryItemName;
}

inline const QString JsonObject::secondaryItem(const int identity)
{
	std::size_t index = identity % 10000;
	if (index < OptionIdentity::SecondaryItemArray.length())
	{
		return OptionIdentity::SecondaryItemArray.at(index);
	}
	return QString();
}

QJsonArray JsonObject::arrFromString(const QString& str)
{
	QStringList list = str.mid(1, str.length() - 2).split(",");
	QStringList::const_iterator iter = list.constBegin();
	QJsonArray arr;
	for (; iter != list.constEnd(); ++iter)
	{
		arr.append(*iter);
	}
	return arr;
}

bool JsonObject::isParent(const int identity)
{
	const int temp = identity % 10000;
	return (temp > 1450) && (temp < 1490);
}

template<typename T>
inline void JsonObject::replace(const int identity, const T& source, const std::size_t index)
{
	const QString parent = primaryItem(identity);
	QJsonArray arr = mainObject.value(parent).toArray();
	if (arr.size() <= index)
	{
		for (int i = 0; i < index - arr.size() + 1; ++i)
		{
			QJsonObject obj;
			arr.append(obj);
		}
	}
	if (isParent(identity))
	{
		mainObject.insert(parent, source);
	}
	else
	{
		const QString child = secondaryItem(identity);
		QJsonObject temp = arr.at(index).toObject();
		temp.insert(child, source);
		arr[index] = temp;
		mainObject.insert(parent, arr);
	}
}


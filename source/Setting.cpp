
#include "..\header\Setting.h"
#include "..\header\filestream.h"
Setting::Setting(const QString& filepath)
{
	QJsonObject path;
	if (!FileStream::readJson(filepath, &path))
	{
		return;
	}
	QJsonArray nameList = path.value("nameList").toArray();
	for (std::size_t i = 0; i < nameList.size(); ++i)
	{
		QString name = nameList.at(i).toString();
		m_pathList.append(path.value(name).toString());
	}

	QFile qssFile;
	for (std::size_t i = 0; i < m_pathList.length(); ++i)
	{
		qssFile.setFileName(m_pathList.at(i));
		if (qssFile.open(QIODevice::ReadOnly))
		{
			m_settings += qssFile.readAll();
			qssFile.close();
		}
	}
	m_pathList.clear();
}

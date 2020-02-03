#pragma once
#include <qobject.h>
#include "openchart.h"
class Setting :public QObject
{
public:
	Setting(const QString& filepath);

	void updateStyle(QWidget* widget)
	{
		widget->setStyleSheet(m_settings);
	}
private:
	QString m_settings;
	QStringList m_pathList;
};


#pragma once
#include <QPlainTextEdit>
#include <QStateMachine>
#include <QMap>
#include <QJsonValue>
#include <QJsonObject>
#include "JsonObject.h"
#include "optionindexfile.h"
class JsonObject;

class CommandLine :public QTextEdit
{
	Q_OBJECT
signals:
	void dataChangedSignal();
	void plotSignal(const QString& name);
	void themeChangeSignal(const QString& theme);
public:
	CommandLine(JsonObject* obj)
	{
		if (obj)
		{
			JsonObj = obj;
		}
		QTextEdit::QTextEdit();
		initForCommandLine();
	}
	void initForCommandLine();
private:
	void keyPressEvent(QKeyEvent* key);
	void splitCommand();
	const int search(const QStringList& strlist);
	const int search(const QString& str);
	const int search(const QString& first, const QString& second);
	void processGet(const int code, const QString& value);
	void processSet(const int code, const QString& value, const int index);
	void processClear(const int code, const int index);
	void display(const QJsonValue& value, const int mode);
	void set_font(const QString& font);
	void set_font_size(const QString& size);
	void errorCommand(const QString& invalidCommand);
private:
	const QString readLine();
private:
	JsonObject* JsonObj;



};

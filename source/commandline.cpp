#include "header/commandline.h"
#include <QFinalState>
#include <QDebug>
#include <QTextBlock>
void CommandLine::initForCommandLine()
{
	this->setFont(QFont("consolas", 14));
}

void CommandLine::keyPressEvent(QKeyEvent* key)
{
	if ((key->key() == Qt::Key::Key_Enter) || (key->key() == Qt::Key::Key_Return))
	{
		splitCommand();
		QTextCursor* tc = &(this->textCursor());
		tc->movePosition(QTextCursor::End);
	}
	QTextEdit::keyPressEvent(key);
}

const QString CommandLine::readLine()
{
	QTextCursor tc = this->textCursor();
	QTextLayout* ty = tc.block().layout();
	const int nCurpos = tc.position() - tc.block().position();
	const int nTextLine = ty->lineForTextPosition(nCurpos).lineNumber() +
		tc.block().firstLineNumber();
	return this->document()->findBlockByLineNumber(nTextLine).text();
}

void CommandLine::splitCommand()
{
	//read line.
	const QString& command = readLine();

	if (command.isEmpty()) {
		return;
	}
	//split by dot.
	const QStringList& commandLayers = command.split(".");
	//the last of split list is always system command and user value.
	const QString& sysAndVal = commandLayers.last();
	//split by ( to get system command and user value.
	const QStringList& sysAndValList = sysAndVal.split("(");
	//get system command.
	const QString& system = sysAndValList.first();
	//get user value.
	const QString& value = sysAndValList.last().left(sysAndValList.last().length() - 1);

	const QMap<QString, int>::const_iterator sys_com =
		CommandLineSet::systemCommand.find(system);
	const QMap<QString, int>::const_iterator sys_end =
		CommandLineSet::systemCommand.constEnd();
	//if system command is valid or not.
	bool found = sys_com != sys_end;
	//command depth depend on if the system command is valid or not.
	const int depth = found ? commandLayers.length() - 1 : commandLayers.length();
	
	int index = 0;
	bool isIndexValid = false;
	QStringList userCommand;
	if (depth > 0)
	{
		//get user command and index.
		userCommand = commandLayers.mid(0, depth);
		if (userCommand.last().contains("("))
		{	//if index exists.
			//split by ( to get user command and index.
			const QStringList& userCommandAndIndex = userCommand.last().split("(");
			//user command
			userCommand.last() = userCommandAndIndex.first();
			//index
			const QString& index_str = userCommandAndIndex.last().left(userCommandAndIndex.last().length() - 1);
			index = index_str.toInt(&isIndexValid);
		}
	}
	const int searchCode = search(userCommand);
	const int systemCommandMode = found ? sys_com.value() :
		(searchCode < 0 ? searchCode : CommandLineSet::SystemCommand::Get);

	switch (systemCommandMode)
	{
	case CommandLineSet::SystemCommand::Cls:
		this->clear();
		break;
	case CommandLineSet::SystemCommand::Exit:
		exit(0);
		break;
	case CommandLineSet::SystemCommand::SetFont:
		this->set_font(value);
		break;
	case CommandLineSet::SystemCommand::setFontSize:
		this->set_font_size(value);
		break;
	case CommandLineSet::SystemCommand::Plot:
		emit plotSignal(value);
		break;
	case CommandLineSet::SystemCommand::Set:
		processSet(searchCode, value, index);
		emit dataChangedSignal();
		break;
	case CommandLineSet::SystemCommand::setTheme:
		emit themeChangeSignal(value);
		break;
	case CommandLineSet::SystemCommand::Get:
		processGet(searchCode, value);
		break;
	case CommandLineSet::Clear:
		processClear(searchCode, index);
		break;
	case CommandLineSet::SystemCommand::ErrorCommand:
		errorCommand(command);
		break;
	default:
		break;
	}
}
const int CommandLine::search(const QStringList& strList)
{
	int code;
	const int depth = strList.length();
	switch (depth)
	{
	case 1:
		code = search(strList.at(0));
		break;
	case 2:
		code = search(strList.at(0), strList.at(1));
		break;
	default:
		code = CommandLineSet::SystemCommand::ErrorCommand;
		break;
	}
	return code;
}
const int CommandLine::search(const QString& str)
{
	int code = CommandLineSet::SystemCommand::ErrorCommand;
	QMap<QString, int>::const_iterator top_command = CommandLineSet::topLayerCommand.find(str);
	QMap<QString, int>::const_iterator end = CommandLineSet::topLayerCommand.constEnd();
	if (top_command != end)
	{
		code = top_command.value();
	}
	else
	{
		QMap<QString, int>::const_iterator sys = CommandLineSet::systemCommand.find(str);
		QMap<QString, int>::const_iterator sys_end = CommandLineSet::systemCommand.constEnd();
		if (sys != sys_end)
		{
			code = sys.value();
		}
	}
	return code;
}
const int CommandLine::search(const QString& first, const QString& second)
{
	int code = CommandLineSet::SystemCommand::ErrorCommand;
	const int topLayer = (search(first) % 10000) - 1451;
	if (topLayer >= 0)
	{
		const QMap<QString, int>& secondCommandRef = 
			CommandLineSet::secondLayerCommand.at(topLayer);
		QMap<QString, int>::const_iterator it = secondCommandRef.find(second);
		QMap<QString, int>::const_iterator end = secondCommandRef.constEnd();
		if (it != end)
		{
			code = it.value();
		}
	}
	return code;
}

void CommandLine::processGet(const int code, const QString& value)
{
	QJsonValue jsonValue;
	JsonObj->get(code, value, &jsonValue);
	display(jsonValue, JsonObj->dataType(code));
}

void CommandLine::processSet(const int code, const QString& value, const int index)
{
	JsonObj->set(code, value, index);
}

void CommandLine::processClear(const int code, const int index)
{
	JsonObj->clear(code, index);
}

void CommandLine::display(const QJsonValue& value, const int dataType)
{
	if (value.isNull())
	{
		this->append("No such an item.");
		return;
	}

	QJsonArray &arr = value.toArray();
	QJsonDocument doc;
	doc.setArray(arr);
	this->append(doc.toJson(QJsonDocument::Indented));
}
void CommandLine::set_font(const QString& font)
{
	QFont newfont;

	const int size = this->font().pixelSize();
	newfont.setFamily(font);
	newfont.setPixelSize(size);
	this->setFont(font);
}

void CommandLine::set_font_size(const QString& size)
{
	bool ok;
	int s = size.toInt(&ok);
	if (ok)
	{
		const QFont newfont(this->font().family(),s);
		this->setFont(newfont);
		qDebug() << s;
	}
	else
	{
		this->append("Error size number.");
	}
}



void CommandLine::errorCommand(const QString& invalidCommand)
{
	QString str("Command ");
	str += "\"";
	str += invalidCommand;
	str += "\"";
	str += " not found.";
	this->append(str);
}


/*
	Copyright (C) OpenChart 2019	email:leonez@nuaa.edu.cn
	Author:wenqiang zhu		
	Time:8-28-2019 23:10

	This file declares some classes which derive from some QWidgets actually.
	These derived classes have its secondary developed slots to suit some signal arguments.
	A function is declared in this file too,this function enabled the widgets when the items on 
the same rows are checked,and disabled the widgets when the items are unchecked.This function is
declared alone out of the classes so all these secondary packaged drived classed can use one piece of code.
	Maybe there are better soluctions to make the function code shared.
	
	Time:8-29-2019 17:53
	I do get a better soluction.
	The widget free function do not need the widget information, it just need the item pointer to show
on which item the widgets need to be enabled or disabled.
	So I put the setWidgetFree function in a class drived from QObject to be a TreeWidgetItemTool class.
When a treeWidgetItem pointer is about to be processed, connect it whih a TreeWidgetItemTool class instance,
*/

#pragma once
#include <QWidget>
#include <QTreeWidget>
#include <QComboBox>
#include <QPushButton>
#include <QSlider>
#include <QLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QKeyEvent>

/*
Drived class to replace QLineEdit.
Two slots are added.
*/
class LineEdit : public QLineEdit
{
	Q_OBJECT
public slots:
	/*
	QLineEdit's setText() slot's secondary package function.
	It takes int value instead of string value as argument
	*/
	void setLineEditStr(const int val);

};

/*
Drived class to replace QSlider.
*/
class Slider: public QSlider
{
	Q_OBJECT
public slots:
	/*
	QSlider's setValue() slot's secondary package function.
	It takes string value instead of int value as argument.
	*/
	void setSliderValue(const QString& str);

};

/*
Drived class to replace QComboBox.
*/
class ComboBox : public QComboBox
{
	Q_OBJECT

};

/*
Drived class to replace QPushButton.
*/
class PushButton :public QPushButton
{
	Q_OBJECT
public:
	PushButton(const QString& text)
	{
		this->setText(text);
	}
	PushButton()
	{
		QPushButton::QPushButton();
	}
public slots:
	/*
	This function keeps the button's background color in sync with the QColorDialog's picked color.
	*/
	void setColor(const QColor& color);
};

class TreeWidgetItemTool :public QObject
{
	Q_OBJECT
public slots:
	void setChecked(QTreeWidgetItem* item,const int column);
	void setFreeWidget(QTreeWidgetItem* item, const int column)
	{
		do_setFreeWidget(item);
	}
private:
	/*
	function that makes widgets on the propertyTreeWidget stay a reasonable enable status.
	argument "item" is a pointer points to the item who's widget is going to be enabled or disabled.
	*/
	void do_setFreeWidget(QTreeWidgetItem* item);
};


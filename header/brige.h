#pragma once

#include <QObject>

#include "openchart.h"
/*
	This is a brige class between clint and HTML page.
*/

class Brige :public QObject
{
	Q_OBJECT
public:
	Brige(OPENCHART* widget,QObject* parent = nullptr)
		:QObject(parent), m_widget(widget)
	{
		connect(m_widget, &OPENCHART::sendMsgSignal, this, &Brige::sendMsg);
		connect(m_widget, &OPENCHART::chartShowLoadingSignal, this, &Brige::showLoading);
		connect(this, &Brige::connected, m_widget, &OPENCHART::connected);
		QObject::connect(this, &Brige::Error, m_widget, &OPENCHART::jsErrorSignal);
	}
	
/*
	this signal will emit from c++ side and be recieved on the HTML side.
*/
signals:
	void sendMsg(const QString& text);
	void showLoading();		//show loading signal from Qt side.
	void connected();
	void Error(const int error);
	
public slots:
	/*
		this slot will be called by the HTML side.
	*/
	void receiveMsg()
	{
		emit connected();
	}
	void jsError(const int code)
	{
		emit Error(code);
	}
private:
	OPENCHART* m_widget;
	
};







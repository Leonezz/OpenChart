#pragma once
#include <QWidget>
#include "openchart.h"
#include "TitleBar.h"
#include "Setting.h"


class WidgetWithTitleBar:public QFrame
{
	Q_OBJECT
public:
	WidgetWithTitleBar(OPENCHART* mainWin);
	bool nativeEvent(const QByteArray& eventType, void* message, long* result);
signals:
	void quitSignal();
protected:
	virtual void closeEvent(QCloseEvent* event);
private:
	bool isPointVaild(const QPoint& point);
	void updateStyleSheet();
	void createConnections();
private:
	QVBoxLayout* layout;
	TitleBar* titlebar;
	OPENCHART* mainWindow;
};


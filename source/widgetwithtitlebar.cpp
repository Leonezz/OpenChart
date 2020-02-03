#include "header/widgetwithtitlebar.h"

#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <Windowsx.h>
#endif

WidgetWithTitleBar::WidgetWithTitleBar(OPENCHART* mainWin)
{
	mainWindow = mainWin;

	titlebar = new TitleBar(this);
	mainWindow->setParent(this);

	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowFlags(Qt::FramelessWindowHint);
	layout = new QVBoxLayout(this);
	titlebar->setObjectName(QString::fromUtf8("TitleBar"));
	installEventFilter(titlebar);
	mainWindow->setObjectName(QString::fromUtf8("MainWindow"));
	layout->addWidget(titlebar);
	layout->addWidget(mainWindow);
	layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(layout);
	updateStyleSheet();
	createConnections();
	//the icon change event has been rewritten in file:TitleBar.cpp function:eventFunction.
	//so here the icon change action actually puts a new image on the iconLabel of customized TitleBar.
	QIcon icon(":/main-128.ico");
	this->setWindowIcon(icon);
}
void WidgetWithTitleBar::closeEvent(QCloseEvent* event)
{
	mainWindow->close();
	titlebar->close();
	emit quitSignal();
}



bool WidgetWithTitleBar::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	//windows API process the mourse event
	Q_UNUSED(eventType)

		MSG* param = static_cast<MSG*>(message);
	
	switch (param->message)
	{
	case WM_NCHITTEST:
	{
		int cursorXPos = GET_X_LPARAM(param->lParam);
		int cursorYPos = GET_Y_LPARAM(param->lParam);
		int cursorToEdgeX = cursorXPos - this->geometry().x();
		int cursorToEdgeY = cursorYPos - this->geometry().y();
		// if cursor lies in the function area,application takes over control
		if (isPointVaild(QPoint(cursorXPos, cursorYPos)))
		{
			return QWidget::nativeEvent(eventType, message, result);
		}
		const int captureBorder = 5;
		// if cursor lies in the zoom border,zoom application
		if ((cursorToEdgeX > -captureBorder) && (cursorToEdgeX < captureBorder))
		{
			*result = HTLEFT;
		}
		if ((cursorToEdgeX > this->width() - captureBorder) && (cursorToEdgeX < this->width() + captureBorder))
		{
			*result = HTRIGHT;
		}
		if ((cursorToEdgeY > -captureBorder) && (cursorToEdgeY < captureBorder))
		{
			*result = HTTOP;
		}
		if ((cursorToEdgeY > this->height() - captureBorder) && (cursorToEdgeY < this->height() + captureBorder))
		{
			*result = HTBOTTOM;
		}
		if ((cursorToEdgeX > -captureBorder) && (cursorToEdgeX < captureBorder) && (cursorToEdgeY > -captureBorder)
			&& (cursorToEdgeY < captureBorder))
		{
			*result = HTTOPLEFT;
		}
		if ((cursorToEdgeX > this->width() - captureBorder) && (cursorToEdgeX < this->width() + captureBorder)
			&& (cursorToEdgeY > -captureBorder) && (cursorToEdgeY < captureBorder))
		{
			*result = HTTOPRIGHT;
		}
		if ((cursorToEdgeX > -captureBorder) && (cursorToEdgeX < captureBorder)
			&& (cursorToEdgeY > this->height() - captureBorder) && (cursorToEdgeY < this->height() + captureBorder))
		{
			*result = HTBOTTOMLEFT;
		}
		if ((cursorToEdgeX > this->width() - captureBorder) && (cursorToEdgeX < this->width() + captureBorder)
			&& (cursorToEdgeY > this->height() - captureBorder) && (cursorToEdgeY < this->height() + captureBorder))
		{
			*result = HTBOTTOMRIGHT;
		}

		return true;
	}
	}

	return QWidget::nativeEvent(eventType, message, result);
}
bool WidgetWithTitleBar::isPointVaild(const QPoint& point)
{
	QRect rect = this->geometry();
	const int pX = point.x();
	const int pY = point.y();
	const int rX = rect.x();
	const int rY = rect.y();
	const int width = rect.width();
	const int height = rect.height();
	return (((pX - rX > 9) && (rX + width - pX > 9)) &&
		((pY - rY > 9) && (rY + height - pY > 9)));
}

void WidgetWithTitleBar::updateStyleSheet()
{
	Setting setting("./Resources/settings/qsspaths.json");
	setting.updateStyle(this);
}

void WidgetWithTitleBar::createConnections()
{
	QObject::connect(titlebar, &TitleBar::openFileActionTriggeredSignal,
		mainWindow, &OPENCHART::openFile);
	QObject::connect(titlebar, &TitleBar::saveActionTriggeredSignal,
		mainWindow, &OPENCHART::saveFile);
	QObject::connect(titlebar, &TitleBar::resourceManagerActionTriggeredSignal,
		mainWindow, &OPENCHART::setFileViewDockWidgetVisable);
	QObject::connect(titlebar, &TitleBar::chartTypeActionTriggeredSignal,
		mainWindow, &OPENCHART::setChartTypeDockWidgetVisable);
	QObject::connect(titlebar, &TitleBar::propertyWidgetActionTriggeredSignal,
		mainWindow, &OPENCHART::setOptionDockWidgetVisable);
	QObject::connect(titlebar, &TitleBar::commandLineActionTriggeredSignal,
		mainWindow, &OPENCHART::setCommandLineDockWidgetvisable);
	QObject::connect(titlebar, &TitleBar::themeMenuActionTriggeredSignal,
		mainWindow, &OPENCHART::chartThemeChangeSlot);
	QObject::connect(mainWindow, &OPENCHART::isWidgetVisableSignal,
		titlebar, &TitleBar::setIconForWindowMenu);
	QObject::connect(mainWindow, &OPENCHART::nowChartTheme, titlebar, &TitleBar::setIconForThemeMenu);
	QObject::connect(titlebar, &TitleBar::openFolderActionTriggeredSignal, 
		mainWindow, &OPENCHART::titleBarOpenFolderActionTriggered);
}


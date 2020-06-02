#include "header/TitleBar.h"
#include "header/filestream.h"
#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

TitleBar::TitleBar(QWidget* parent)
	:QWidget(parent), icon(QIcon(":/yes_1296db_200.svg"))
{
	this->setFixedHeight(28);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setWindowFlags(Qt::FramelessWindowHint);

	createLayout();
}


void TitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
	Q_UNUSED(event);
	emit b_sizeButton->clicked();
}

void TitleBar::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isLeftButtonClicked = true;
		p_startPoint = QCursor::pos();
	}
}

void TitleBar::mouseMoveEvent(QMouseEvent* event)
{
#ifdef Q_OS_WIN
	if (ReleaseCapture())
	{
		QWidget* pWindow = this->window();
		if (pWindow->isTopLevel())
		{
			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
		}
	}
	event->ignore();
#else
	//code for other platform here.
#endif
}

void TitleBar::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_isLeftButtonClicked = false;
	}
}

bool TitleBar::eventFilter(QObject* obj, QEvent* event)
{
	QWidget* pWidget = qobject_cast<QWidget*>(obj);
	switch (event->type())
	{
	case QEvent::WindowTitleChange:
		if (pWidget)
		{
			l_titleLabel->setText(pWidget->windowTitle());
			return true;
		}
	case QEvent::WindowIconChange:
		if (pWidget)
		{
			QIcon icon = pWidget->windowIcon();
			l_iconLabel->setPixmap(icon.pixmap(l_iconLabel->size()));
			return true;
		}
	case QEvent::WindowStateChange:
	case QEvent::Resize:
		updateWindowSize();
		return true;
	}
	return QWidget::eventFilter(obj, event);
}

void TitleBar::themeMunuActionTriggeredSlot(QAction* action)
{
	if (action != NULL)
	{
		QString name = action->objectName();
		emit themeMenuActionTriggeredSignal(name);
	}
}

void TitleBar::donateActionTriggeredSlot()
{
	QDesktopServices::openUrl(QUrl("file:///C:/Users/zhuWenQ/Desktop/Study/C++/Qt/OpenChart_demo/Untitled-1.html"));
}

void TitleBar::addAction(const QString& text, QMenu** parent, QAction** action, const QString& name)
{
	(*action) = new QAction(text, this);
	(*action)->setObjectName(name);
	(*parent)->addAction(*action);
}

void TitleBar::addAction(const QString& text, QMenuBar** parent, QAction** action, const QString& name)
{
	(*action) = new QAction(text, this);
	(*action)->setObjectName(name);
	(*parent)->addAction(*action);
}

void TitleBar::addMenu(const QString& text, QMenuBar** parent, QMenu** menu, const QString& name)
{
	(*menu) = new QMenu(text, this);
	(*menu)->setObjectName(name);
	(*parent)->addMenu(*menu);
}

void TitleBar::addMenu(const QString& text, QMenu** parent, QMenu** menu, const QString& name)
{
	(*menu) = new QMenu(text, this);
	(*menu)->setObjectName(name);
	(*parent)->addMenu(*menu);
}

void TitleBar::createMenuBar()
{
	//menuBar
	m_menuBar = new QMenuBar(this);
	m_menuBar->setObjectName(QString::fromUtf8("MenuBar"));
	m_menuBar->setFont(QFont("consolas", 11));
	m_menuBar->setContentsMargins(0, 0, 0, 0);
	//m_menuBar->setGeometry(30, 0, 1000, 30);
	//fileMenu
	addMenu(tr("文件(&F)"), &m_menuBar, &m_fileMenu);
	addAction(tr("打开文件"), &m_fileMenu, &a_openFileAction);
	addAction(tr("打开文件夹"), &m_fileMenu, &a_openFolderAction);
	addAction(tr("保存"), &m_fileMenu, &a_saveAction);
	addAction(tr("另存为"), &m_fileMenu, &a_saveAsAction);
	addAction(tr("退出"), &m_fileMenu, &a_quitAction);

	//windowsMenu
	addMenu(tr("窗口(&W)"), &m_menuBar, &m_windowsMenu);
	addAction(tr("资源管理器"), &m_windowsMenu, &a_resourceManagerAction, "ResourcesManager");
	addAction(tr("图表类型"), &m_windowsMenu, &a_chartTypeAction, "ChartType");
	addAction(tr("命令行"), &m_windowsMenu, &a_commandLineAction, "CommandLine");
	addAction(tr("配置项"), &m_windowsMenu, &a_propertyEditAction, "Property");
	//themeMenu
	addMenu(tr("主题(&T)"), &m_menuBar, &m_themeMenu);
	QJsonObject themeList;
	if (FileStream::readJson("./Resources/theme/themeList.json", &themeList))
	{
		QJsonArray nameList = themeList.value("nameList").toArray();
		for (std::size_t i = 0; i < nameList.size(); ++i)
		{
			const QString name = nameList.at(i).toString();
			QAction* themeAction = new QAction(name, this);
			themeAction->setObjectName(name);
			themeActionList.append(themeAction);
		}
	}
	m_themeMenu->addActions(themeActionList);


	//helpMenu
	addMenu(tr("帮助(&H)"), &m_menuBar, &m_helpMenu);
	addAction(tr("教程"), &m_helpMenu, &a_tutorialAction);
	addAction(tr("关于此软件"), &m_helpMenu, &a_aboutThisAction);
	//donate
	addAction(tr("捐赠"), &m_menuBar, &a_donateAction);
}

void TitleBar::createLabels()
{
	l_iconLabel = new QLabel(this);
	l_iconLabel->setFixedSize(30, 30);
	l_iconLabel->setObjectName(QString::fromUtf8("Icon"));

	l_titleLabel = new QLabel(tr("OpenChart"), this);
	l_titleLabel->setFixedHeight(30);
	l_titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	l_titleLabel->setFont(QFont("consolas", 10));
	l_titleLabel->setObjectName(QString::fromUtf8("Title"));
}

void TitleBar::createButtons()
{
	b_minimizeButton = new QPushButton(this);
	b_minimizeButton->setObjectName(QString::fromUtf8("MinimizeButton"));
	b_minimizeButton->setFixedSize(30, 30);
	b_sizeButton = new QPushButton(this);
	b_sizeButton->setObjectName(QString::fromUtf8("NormalButton"));
	b_sizeButton->setFixedSize(30, 30);
	b_closeButton = new QPushButton(this);
	b_closeButton->setObjectName(QString::fromUtf8("CloseButton"));
	b_closeButton->setFixedSize(30, 30);

	QObject::connect(b_closeButton, &QPushButton::clicked, this, &TitleBar::titleBarButton_clicked);
	QObject::connect(b_sizeButton, &QPushButton::clicked, this, &TitleBar::titleBarButton_clicked);
	QObject::connect(b_minimizeButton, &QPushButton::clicked, this, &TitleBar::titleBarButton_clicked);
}

void TitleBar::createLayout()
{
	createLabels();
	createMenuBar();
	createButtons();

	m_layout = new QHBoxLayout(this);
	m_layout->addWidget(l_iconLabel);
	m_layout->addSpacing(5);
	m_layout->addWidget(m_menuBar);

	m_lspacer = new QSpacerItem(300, 30, QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_layout->addSpacerItem(m_lspacer);
	m_rspacer = new QSpacerItem(300, 30, QSizePolicy::Expanding, QSizePolicy::Fixed);
	m_layout->addWidget(l_titleLabel);
	m_layout->addSpacerItem(m_rspacer);
	m_layout->addWidget(b_minimizeButton);
	m_layout->addWidget(b_sizeButton);
	m_layout->addWidget(b_closeButton);
	m_layout->setContentsMargins(0, 0, 0, 0);
	this->setLayout(m_layout);

	createConnections();
}

void TitleBar::createConnections()
{
	QObject::connect(a_openFileAction, &QAction::triggered, this, &TitleBar::openFileActionTriggeredSignal);
	QObject::connect(a_openFolderAction, &QAction::triggered, this, &TitleBar::openFolderActionTriggeredSignal);
	QObject::connect(a_saveAction, &QAction::triggered, this, &TitleBar::saveActionTriggeredSignal);
	QObject::connect(a_saveAsAction, &QAction::triggered, this, &TitleBar::saveAsActionTriggeredSignal);
	QObject::connect(a_quitAction, &QAction::triggered, this, &TitleBar::quitActionTriggeredSlot);
	QObject::connect(a_chartTypeAction, &QAction::triggered, this, &TitleBar::chartTypeActionTriggeredSignal);
	QObject::connect(a_commandLineAction, &QAction::triggered, this, &TitleBar::commandLineActionTriggeredSignal);
	QObject::connect(a_propertyEditAction, &QAction::triggered, this, &TitleBar::propertyWidgetActionTriggeredSignal);
	QObject::connect(a_resourceManagerAction, &QAction::triggered, this, &TitleBar::resourceManagerActionTriggeredSignal);

	QObject::connect(a_tutorialAction, &QAction::triggered, this, &TitleBar::tutorialActionTriggeredSignal);
	QObject::connect(a_aboutThisAction, &QAction::triggered, this, &TitleBar::aboutThisActionTriggeredSignal);
	QObject::connect(a_donateAction, &QAction::triggered, this, &TitleBar::donateActionTriggeredSlot);

	QObject::connect(m_themeMenu, &QMenu::triggered, this, &TitleBar::themeMunuActionTriggeredSlot);
}

void TitleBar::quitActionTriggeredSlot()
{
	b_closeButton->clicked();
}

void TitleBar::updateWindowSize()
{
	QWidget* pWidget = this->window();
	if (pWidget->isTopLevel())
	{
		bool bMaximize = pWidget->isMaximized();
		if (bMaximize)
		{
			b_sizeButton->setToolTip(tr("Restore"));
			b_sizeButton->setProperty("maximizeProperty", "restore");
		}
		else
		{
			b_sizeButton->setProperty("maximizeProperty", "maximize");
			b_sizeButton->setToolTip(tr("Maximize"));
		}
	}
}

void TitleBar::setIconForThemeMenu(const QString& name)
{
	for (std::size_t i = 0; i < themeActionList.length(); ++i)
	{
		QAction* action = themeActionList.at(i);
		action->setIconVisibleInMenu(false);
		if (action->objectName() == name)
		{
			action->setIcon(icon);
			action->setIconVisibleInMenu(true);
		}
	}
}

void TitleBar::setIconForWindowMenu(const int i, bool flag)
{
	QAction* action;
	switch (i)
	{
	case ChartTypeMenuAction:
		action = a_chartTypeAction;
		break;
	case CommandLineMenuAction:
		action = a_commandLineAction;
		break;
	case ResourceManager:
		action = a_resourceManagerAction;
		break;
	case PropertyMenuAction:
		action = a_propertyEditAction;
		break;
	default:
		return;
		break;
	}
	if (action)
	{
		action->setIcon(icon);
		action->setIconVisibleInMenu(flag);
	}
}

void TitleBar::titleBarButton_clicked()
{
	QPushButton* pBtn = qobject_cast<QPushButton*>(sender());
	QWidget* pWindow = this->window();
	if (pWindow->isWindow())
	{
		if (pBtn == b_minimizeButton)
		{
			pWindow->showMinimized();
		}
		else if (pBtn == b_sizeButton)
		{
			pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
		}
		else if (pBtn == b_closeButton)
		{
			pWindow->close();
		}
	}
}

void TitleBar::onClicked()
{
	QPushButton* pButton = qobject_cast<QPushButton*>(sender());
	QWidget* pWindow = this->window();
	if (pWindow->isTopLevel())
	{
		if (pButton == b_minimizeButton)
		{
			pWindow->showMinimized();
		}
		else if (pButton == b_sizeButton)
		{
			pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
		}
		else if (pButton == b_closeButton)
		{
			pWindow->close();
		}
	}
}


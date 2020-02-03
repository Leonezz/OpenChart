#pragma once
#include <QtCore>
#include <QLabel>
#include <QAction>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QButtonGroup>
#include <QLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QDeskTopWidget>
#include <QApplication>
#include <qdesktopservices.h>
enum {
	ChartTypeMenuAction=0,
	CommandLineMenuAction=1,
	PropertyMenuAction=2,
	VintageMenuAction=3,
	DarkMenuAction=4,
	MacaronsMenuAction=5,
	InfographicMenuAction=6,
	RomaMenuAction=7,
	ShineMenuAction=8,
	ResourceManager = 9
};
class TitleBar:public QWidget
{
	Q_OBJECT
public:
	TitleBar(QWidget* parent = nullptr);
public slots:
	void setIconForThemeMenu(const QString& name);
	void setIconForWindowMenu(const int index, bool flag);
	void titleBarButton_clicked();
protected:
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);
	virtual bool eventFilter(QObject* obj, QEvent* event);
protected slots:
	void onClicked();
signals:
	void resourceManagerActionTriggeredSignal();
	void openFileActionTriggeredSignal();
	void openFolderActionTriggeredSignal();
	void saveActionTriggeredSignal();
	void saveAsActionTriggeredSignal();
	void chartTypeActionTriggeredSignal();
	void commandLineActionTriggeredSignal();
	void propertyWidgetActionTriggeredSignal();
	void mainWidgetActionTriggeredSignal();
	void tutorialActionTriggeredSignal();
	void aboutThisActionTriggeredSignal();
	void themeMenuActionTriggeredSignal(const QString& name);
private slots:
	void quitActionTriggeredSlot();
	void themeMunuActionTriggeredSlot(QAction* action);
	void donateActionTriggeredSlot();
private:
	void addAction(const QString& text, QMenu** parent, QAction** action, const QString& name = "ItemAction");
	void addAction(const QString& text, QMenuBar** parent, QAction** action, const QString& name = "MenuAction");
	void addMenu(const QString& text, QMenuBar** parent, QMenu** menu, const QString& name = "Menu");
	void addMenu(const QString& text, QMenu** parent, QMenu** menu, const QString& name = "ItemMenu");
	void createMenuBar();
	void createLabels();
	void createButtons();
	void createLayout();
	void createConnections();
	void updateWindowSize();
private:
	QIcon icon;

	QLabel* l_iconLabel;
	QLabel* l_titleLabel;

	QAction* a_openFileAction;
	QAction* a_openFolderAction;
	QAction* a_saveAction;
	QAction* a_saveAsAction;
	QAction* a_quitAction;

	QAction* a_resourceManagerAction;
	QAction* a_chartTypeAction;
	QAction* a_commandLineAction;
	QAction* a_propertyEditAction;

	QList<QAction*> themeActionList;

	QAction* a_tutorialAction;
	QAction* a_aboutThisAction;
	QAction* a_donateAction;

	QMenuBar* m_menuBar;
	QMenu* m_fileMenu;
	QMenu* m_windowsMenu;
	QMenu* m_themeMenu;
	QMenu* m_helpMenu;

	QPushButton* b_closeButton;
	QPushButton* b_sizeButton;
	QPushButton* b_minimizeButton;

	QHBoxLayout* m_layout;
	QSpacerItem* m_lspacer;
	QSpacerItem* m_rspacer;

	bool m_isLeftButtonClicked;
	QPoint p_startPoint;
	QPoint p_endPoint;
};

#pragma execution_character_set("utf-8")	//set char-set to utf-8
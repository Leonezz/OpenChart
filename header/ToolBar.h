#pragma once
#include <qtoolbar.h>
#include <QPushButton>
class ToolBar :public QToolBar
{
	Q_OBJECT
public:
	ToolBar();
private:
	void createConnections();
signals:
	void resourceButtonClickedSignal();
	void searchButtonClickedSignal();
	void choseChartTypeButtonClickedSignal();
	void editOptionButtonClickedSignal();
	void settingButtonClickedSignal();
private:
	QPushButton* m_resourceButton;
	QPushButton* m_searchButton;
	QPushButton* m_choseChartTypeButton;
	QPushButton* m_editOptionButton;
	QPushButton* m_settingButton;
};


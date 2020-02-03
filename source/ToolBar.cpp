#include "header/ToolBar.h"


ToolBar::ToolBar()
{
	m_resourceButton = new QPushButton();
	m_resourceButton->setObjectName(QString::fromUtf8("Resources"));
	m_resourceButton->setFixedSize(50, 50);
	this->addWidget(m_resourceButton);

	m_searchButton = new QPushButton();
	m_searchButton->setObjectName(QString::fromUtf8("Serach"));
	m_searchButton->setFixedSize(50, 50);
	this->addWidget(m_searchButton);

	m_choseChartTypeButton = new QPushButton();
	m_choseChartTypeButton->setObjectName(QString::fromUtf8("ChartType"));
	m_choseChartTypeButton->setFixedSize(50, 50);
	this->addWidget(m_choseChartTypeButton);

	m_editOptionButton = new QPushButton();
	m_editOptionButton->setObjectName(QString::fromUtf8("Edit"));
	m_editOptionButton->setFixedSize(50, 50);
	this->addWidget(m_editOptionButton);

	QWidget* spacer = new QWidget();
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->addWidget(spacer);		//add a widget as a spacer to make my action be bottom

	m_settingButton = new QPushButton();
	m_settingButton->setObjectName(QString::fromUtf8("Setting"));
	m_settingButton->setFixedSize(50, 50);
	this->addWidget(m_settingButton);

	this->setFixedWidth(50);
	this->setIconSize(QSize(46, 46));

	this->setWindowFlag(Qt::FramelessWindowHint);
	this->setFloatable(false);
	this->setMovable(false);

	createConnections();
}

void ToolBar::createConnections()
{
	QObject::connect(m_resourceButton, &QPushButton::clicked, this, &ToolBar::resourceButtonClickedSignal);
	QObject::connect(m_searchButton, &QPushButton::clicked, this, &ToolBar::searchButtonClickedSignal);
	QObject::connect(m_choseChartTypeButton, &QPushButton::clicked, this, &ToolBar::choseChartTypeButtonClickedSignal);
	QObject::connect(m_editOptionButton, &QPushButton::clicked, this, &ToolBar::editOptionButtonClickedSignal);
	QObject::connect(m_settingButton, &QPushButton::clicked, this, &ToolBar::settingButtonClickedSignal);
}

#include <QSizePolicy>
#include <QFontComboBox>
#include <QModelIndex>

#include "header/openchart.h"
#include "header/openchartprivate.h"
#include "header/JsonObject.h"
#include "header/sliderandlineedit.h"


const QString htmlFileFolderPath = "/Resources/html/";
const QString jsFileFolderPath = "/Resources/js/";
const QString jsonFileFolderPath = "/Resources/json/";
OPENCHART::OPENCHART(QWidget* parent)
	: QMainWindow(parent),isOptionChanged(false),isUserInput(false),d_ptr(new OpenChartPrivate)
{
	ui.setupUi(this);
	this->setAttribute(Qt::WA_DeleteOnClose);

	webView = new WebViewInNewThread();
	this->setCentralWidget(webView->get());
	QObject::connect(this, &OPENCHART::webViewLoad, webView, &WebViewInNewThread::loadPageByUrl);

	toolBar = new ToolBar();
	this->addToolBar(Qt::ToolBarArea::LeftToolBarArea, toolBar);

	this->setCorner(Qt::Corner::BottomLeftCorner, Qt::DockWidgetArea::LeftDockWidgetArea);
	this->setCorner(Qt::Corner::BottomRightCorner, Qt::DockWidgetArea::RightDockWidgetArea);
	fileView = new FileModelView();
	this->addDockWidget(Qt::LeftDockWidgetArea, fileView);
	this->addDockWidget(Qt::LeftDockWidgetArea, ui.chartTypeDockWidget);
	this->addDockWidget(Qt::LeftDockWidgetArea, ui.configDockWidget);
	this->addDockWidget(Qt::BottomDockWidgetArea, ui.commandLineConfigDockWidget);
	ui.configDockWidget->hide();
	fileView->hide();

	commandLine = new CommandLine(&(d_ptr->option));//important

	ui.commandLineConfigDockWidget->setWidget(commandLine);

	createStatusBar();
	ui.chartTypeTreeWidget->setColumnHidden(1, true);
	ui.chartTypeTreeWidget->setColumnHidden(2, true);

	ui.propertySetTreeWidget->setColumnHidden(2, true);
	ui.propertySetTreeWidget->setColumnHidden(3, true);

	QHeaderView* head = ui.propertySetTreeWidget->header();
	head->setSectionResizeMode(0,QHeaderView::ResizeToContents);
	head->setSectionResizeMode(2,QHeaderView::ResizeToContents);
	head->setSectionResizeMode(1,QHeaderView::Stretch);

	initPropertyTreeWidget();
	
	QObject::connect(commandLine, &CommandLine::plotSignal, 
		this, &OPENCHART::plotSlot);
	QObject::connect(commandLine, &CommandLine::themeChangeSignal,
		this, &OPENCHART::chartThemeChangeSlot);
	createConnections();

	basicPlot("basic");
}

void OPENCHART::plotSlot(const QString& name)
{
	const QMap<QString, int>::const_iterator index = chartTypeMap.find(name);
	const QMap<QString, int>::const_iterator end = chartTypeMap.constEnd();
	if (index == end)
	{
		return;
	}
	//reloadChart(name);
	QModelIndex modelIndex = ui.chartTypeTreeWidget->model()->index(index.value(), 0);
	ui.chartTypeTreeWidget->setCurrentIndex(modelIndex);
	//int a = index.value();
	QTreeWidgetItem* item = ui.chartTypeTreeWidget->currentItem();
	initChart(item, 0);
}

void OPENCHART::setChartTheme(const QString& themeName)
{
	if (!themeName.isEmpty())
	{
		basicPlot(themeName);
		emit nowChartTheme(themeName);
	}
}

void OPENCHART::chartThemeChangeSlot(const QString& theme)
{
	setChartTheme(theme);
}

void OPENCHART::createConnections()
{
	QObject::connect(ui.chartTypeTreeWidget, &QTreeWidget::itemActivated,
		this, &OPENCHART::initChart);	//change chart
	//QObject::connect(this, &OPENCHART::optionChangedSignal, this, &OPENCHART::optionChangedSlot);
	QObject::connect(&(d_ptr->option), &JsonObject::valueChanged,
		this, &OPENCHART::optionChangedSlot);
	QObject::connect(this, &OPENCHART::jsErrorSignal, d_ptr, &OpenChartPrivate::backStuff);

	QObject::connect(toolBar, &ToolBar::resourceButtonClickedSignal,
		this, &OPENCHART::toolBarResourceButtonClickedSlot);
	QObject::connect(toolBar, &ToolBar::searchButtonClickedSignal,
		this, &OPENCHART::toolBarSearchButtonClickedSlot);
	QObject::connect(toolBar, &ToolBar::choseChartTypeButtonClickedSignal,
		this, &OPENCHART::toolBarChoseChartTypeButtonClickedSolt);
	QObject::connect(toolBar, &ToolBar::editOptionButtonClickedSignal,
		this, &OPENCHART::toolBarEditOptionButtonClickedSlot);
	QObject::connect(toolBar, &ToolBar::settingButtonClickedSignal,
		this, &OPENCHART::toolBarSettingButtonClickedSlot);

	QObject::connect(fileView, &QDockWidget::visibilityChanged,
		this, &OPENCHART::isFileViewWidgetVisable);
	QObject::connect(ui.chartTypeDockWidget, &QDockWidget::visibilityChanged,
		this, &OPENCHART::isChartTypeWidgetVisable);
	QObject::connect(ui.configDockWidget, &QDockWidget::visibilityChanged,
		this, &OPENCHART::isProertyWidgetVisable);
	QObject::connect(ui.commandLineConfigDockWidget, &QDockWidget::visibilityChanged,
		this, &OPENCHART::isCommandLineVisable);

	QObject::connect(fileView, &FileModelView::sendFileDataSignal, this, &OPENCHART::feedFileDataToJson);
	QObject::connect(fileView, &FileModelView::sendJsonDataSignal, this, &OPENCHART::jsonFromUser);
	QObject::connect(fileView, &FileModelView::fileItemDoubleClicked, this, &OPENCHART::loadFileByName);
	QObject::connect(this, &OPENCHART::loadFileInNewThreadSignal, fileView, &FileModelView::loadFile);
}


void OPENCHART::connected()
{
	QString str = DataProcess::jsonToString(d_ptr->option.get());
	emit sendMsgSignal(str);
}

void OPENCHART::createMenuBar()
{
	QWidget* widget = new QWidget();
	widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
}

void OPENCHART::createStatusBar()
{
	d_ptr->curChartLabel = new QLabel("Type：", this);
	d_ptr->curChartLabel->setObjectName("CurrentTypeLabel");
	d_ptr->curChartLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);

	d_ptr->curChartLabel->setContentsMargins(0, 0, 0, 0);
	statusBar()->setFixedHeight(22);
	statusBar()->addWidget(d_ptr->curChartLabel);
	
	QPushButton* github = new QPushButton();
	github->setObjectName("Github");
	github->setFixedWidth(22);
	github->setContentsMargins(0, 0, 0, 0);
	this->statusBar()->addPermanentWidget(github);
	
	QObject::connect(this, &OPENCHART::updateStatusBarSignal, this, &OPENCHART::updateStatusBar);
}


void OPENCHART::updateStatusBar()
{
	QString str = "Type: ";
	str += d_ptr->curChartType;
	d_ptr->curChartLabel->setText(str);
}

void OPENCHART::openFile()
{
	QString filePath = QFileDialog::getOpenFileName(this, tr("OpenChart"),
		".", tr("Microsoft Excel Forms(*.xlsx);\n\
				 JavaScript Object Notation(*.json)\n\
				Comma-Separated Values(*.csv)"));
	if (filePath.isEmpty())
	{
		QMessageBox::warning(this, tr("OpenFile"), tr("Empty File Path."), QMessageBox::Yes);
	}
	else
	{
		loadFileByName(filePath);
	}
}


void OPENCHART::initPropertyTreeWidget()
{
	/*
	1-----lineedit
	2-----combobox
	3-----colorpicker
	4-----lineedit
	*/
	enum WidgetType
	{
		LineEdit=1,
		ComboBox=2,
		ColorPicker=3,
		FontPicker=5
	};
	TreeWidgetItemTool* itemHelper = new TreeWidgetItemTool();
	QObject::connect(ui.propertySetTreeWidget, &QTreeWidget::itemDoubleClicked,
		itemHelper, &TreeWidgetItemTool::setChecked);
	QObject::connect(ui.propertySetTreeWidget, &QTreeWidget::itemClicked, 
		itemHelper, &TreeWidgetItemTool::setFreeWidget);

	QTreeWidgetItemIterator iter(ui.propertySetTreeWidget);
	while (*iter)
	{
		const int flag = (*iter)->text(2).toInt();
		switch (flag)
		{
		case WidgetType::ComboBox:
			addComboBox(*iter);
			break;
		case WidgetType::ColorPicker:
			addColorPicker(*iter);
			break;
		case WidgetType::LineEdit:
			addLineEdit(*iter);
			break;
		case WidgetType::FontPicker:
			addFontPicker(*iter);
			break;
		}
		++iter;
	}
}

void OPENCHART::addWidgetToTreeWidget(QTreeWidgetItem* item, const int column, QWidget* widget)
{
	//widget->setFixedWidth(30);
	ui.propertySetTreeWidget->setItemWidget(item, column, widget);
}


void OPENCHART::addComboBox(QTreeWidgetItem* item)
{
	ComboBox* combo = new ComboBox();
	combo->setEnabled(false);
	addWidgetToTreeWidget(item, 1, combo);
}

void OPENCHART::addLineEdit(QTreeWidgetItem* item)
{
	LineEdit* edit = new LineEdit();
	edit->setEnabled(false);
	QFont font;
	font.setFamily("consolas");
	font.setPixelSize(14);
	edit->setFont(font);
	addWidgetToTreeWidget(item, 1, edit);
}

void OPENCHART::addColorPicker(QTreeWidgetItem* item)
{
	QColorDialog* dialog = new QColorDialog();
	PushButton* push = new PushButton();
	push->setObjectName(QString::fromUtf8("ColorPickerButton"));
	push->setEnabled(false);
	addWidgetToTreeWidget(item, 1, push);
	QObject::connect(push, &QPushButton::clicked, dialog, &QColorDialog::exec);
	QObject::connect(dialog, &QColorDialog::colorSelected, push, &PushButton::setColor);
}

void OPENCHART::addFontPicker(QTreeWidgetItem* item)
{
	QFontComboBox* fontbox = new QFontComboBox();
	fontbox->setEnabled(false);
	addWidgetToTreeWidget(item, 1, fontbox);
}

void OPENCHART::openJson(const QString& filePath)
{
	//json file should be complete.
	jsonFromInit(FileStream::readJson(filePath));
}

void OPENCHART::basicPlot(const QString& chartType)
{
	QUrl basicPage = QUrl::fromLocalFile(htmlFileFolderPath + chartType + ".html");
	//ui.mainWidget->load(basicPage);
	emit webViewLoad(basicPage);
}

void OPENCHART::saveFile()
{
	QString m_filePath = d_ptr->filePath;
	
	if (isOptionChanged||!QFile::exists(m_filePath))
	{
		m_filePath = QFileDialog::getSaveFileName(this,
			tr("Sava"), ".", tr("JavaScript Object Notation files (*.json)\n"
				"Excel表格 (*.xlsx)\n"
				"Comma-separated values file (*.csv)\n"
				"标准文本文档 (*.txt)"));
	}
	QJsonDocument doc;
	doc.setObject(d_ptr->option.get());
	QFile file(m_filePath);
	if (file.open(QIODevice::WriteOnly))
	{
		file.write(doc.toJson());
		isOptionChanged = false;
		isUserInput = false;
		d_ptr->filePath = m_filePath;
		d_ptr->lastItem->setText(1, m_filePath);	//change the last item's text.
		file.close();
	}
	else
	{
		QMessageBox::warning(this, tr("保存失败!"),
			tr("文件打开错误：" + file.error()), QMessageBox::Ok);
	}

}

/*
	this function will be called when items on the tree widget are activated.
	if some changes are made to an example plot,when another item actived,save messagebox on.
	if save button is chosen,file will be saved and antoher time you activated the very item which you
chose before saving(that one you made your changes on),your changed plot will be on(widget load your 
saved file instead of the example file).
*/
void OPENCHART::initChart(QTreeWidgetItem* item, int column)
{
	QString str = item->text(1);		//get item text which will be used as file adress.
	int flag = 0;						//recoad messagebox button pressed status.
	if (isOptionChanged&&isUserInput)
	{
		switch (QMessageBox::warning(this, tr("Warning!"),
			tr("You are try to leave this page.\n Are you sure to leave without save your changes?"),
			QMessageBox::Save | QMessageBox::No|QMessageBox::Yes,
			QMessageBox::Yes))
		{
		case QMessageBox::Yes:
			isOptionChanged = false;
			isUserInput = false;
			break;
		case QMessageBox::Save:
			saveFile();
			flag = 1;
			break;
		case QMessageBox::No:
		default:
			flag = 2;
			break;
		}
	}
	if (flag == 0)
	{
		/*
		this statement stays here not the begin of this function.
		otherwise curChartIndex may update a wrong value. 
		*/
		d_ptr->curChartIndex = item->text(2).toInt();	
		d_ptr->curChartType = str;
		reloadChart(str);
		d_ptr->lastItem = item;
		emit updateStatusBarSignal();
	}
}

void OPENCHART::setChartTypeDockWidgetVisable()
{
	ui.chartTypeDockWidget->isVisible() ? 
		ui.chartTypeDockWidget->hide() : ui.chartTypeDockWidget->show();
}

void OPENCHART::setCommandLineDockWidgetvisable()
{
	
	 ui.commandLineConfigDockWidget->isVisible() ? 
		 ui.commandLineConfigDockWidget->hide() : ui.commandLineConfigDockWidget->show();
}

void OPENCHART::setOptionDockWidgetVisable()
{
	ui.configDockWidget->isVisible() ? 
		ui.configDockWidget->hide() : ui.configDockWidget->show();
}

void OPENCHART::setFileViewDockWidgetVisable()
{
	fileView->isVisible() ? fileView->hide() : fileView->show();
}

void OPENCHART::titleBarOpenFolderActionTriggered()
{
	fileView->buildFileTree();
}

void OPENCHART::toolBarResourceButtonClickedSlot()
{
	setFileViewDockWidgetVisable();
	ui.chartTypeDockWidget->hide();
	ui.configDockWidget->hide();
}

void OPENCHART::toolBarSearchButtonClickedSlot()
{

}

void OPENCHART::toolBarChoseChartTypeButtonClickedSolt()
{
	setChartTypeDockWidgetVisable();
	ui.configDockWidget->hide();
	fileView->hide();
}

void OPENCHART::toolBarEditOptionButtonClickedSlot()
{
	setOptionDockWidgetVisable();
	ui.chartTypeDockWidget->hide();
	fileView->hide();
}



void OPENCHART::toolBarSettingButtonClickedSlot()
{

}

void OPENCHART::loadFileByName(const QString& fileName)
{
	const QString fileType = fileName.split(".").last();
	const int i_fileType = (fileType == "xlsx") ? 1 :
		((fileType == "csv") ? 2 :
		((fileType == "txt") ? 3 :
			((fileType == "json") ? 4 : 0)));
	if (i_fileType != 0)
	{
		emit loadFileInNewThreadSignal(fileName, i_fileType);
		emit chartShowLoadingSignal();
	}
}

void OPENCHART::reloadChart(const QString& str)
{
	QString path = str;//make a copy.
	if (str.split(".").length() == 1)
	{
		path = "./Resources/json/" + path + ".json";
	}
	QJsonObject option = FileStream::readJson(path);
	jsonFromInit(option);
}


void OPENCHART::optionChangedSlot()
{
	QString str = DataProcess::jsonToString(d_ptr->option.get());
	isOptionChanged = true;
	isUserInput = true;
	emit sendMsgSignal(str);
}

void OPENCHART::jsonFromUser(const QJsonObject& json)
{
	d_ptr->option = json;
}

void OPENCHART::jsonFromInit(const QJsonObject& json)
{
	d_ptr->option = json;
	isUserInput = false;
}

void OPENCHART::feedFileDataToJson(QList<QList<QVariant> > dataList)
{
	isOptionChanged = true;
	isUserInput = true;
	auto processAndFeedDataConcurrently = [&](const QList<QList<QVariant> >& list) {
		switch (d_ptr->curChartIndex)
		{
		case Line:
			DataProcess::dataForLine(list, &d_ptr->option);
			break;
		case Bar:
			DataProcess::dataForBar(list, &d_ptr->option);
			break;
		case CPie:
			DataProcess::dataForPie(list, &d_ptr->option);
			break;
		case Scatter:
			DataProcess::dataForScatter(list, &d_ptr->option);
			break;
		case Flow:
			DataProcess::dataForFlow(list, &d_ptr->option);
			break;
		case KLine:
			DataProcess::dataForKLine(list, &d_ptr->option);
			break;
		case Radar:
			DataProcess::dataForRadar(list, &d_ptr->option);
			break;
		case BoxPlot:
			DataProcess::dataForBoxplot(list, &d_ptr->option);
			break;
		case HeatMap:
			DataProcess::dataForHeatmap(list, &d_ptr->option);
			break;
		case Relation:
			DataProcess::dataForRelation(list, &d_ptr->option);
			break;
		case Tree:
			DataProcess::dataForTree(list, &d_ptr->option);
			break;
		case RectangleTree:
			DataProcess::dataForTreeMap(list, &d_ptr->option);
			break;
		case Sun:
			DataProcess::dataForSun(list, &d_ptr->option);
			break;
		case ParallelCoordinateSystem:
			DataProcess::dataForParallelCoordinates(list, &d_ptr->option);
			break;
		case Sankey:
			DataProcess::dataForSankey(list, &d_ptr->option);
			break;
		case Funnel:
			DataProcess::dataForFunnel(list, &d_ptr->option);
			break;
		case Polar:
			DataProcess::dataForPolar(list, &d_ptr->option);
			break;
		case River:
			DataProcess::dataForRiver(list, &d_ptr->option);
			break;
		case Calendar:
			DataProcess::dataForCalendar(list, &d_ptr->option);
			break;
		case Dataset:
			DataProcess::dataForDataSet(list, &d_ptr->option);
			break;
		case D3Bar:
			DataProcess::dataForBar3D(list, &d_ptr->option);
			break;
		case D3Surface:
			DataProcess::dataForScatter3D(list, &d_ptr->option);
			break;
		case D3Line:
			DataProcess::dataForLine3D(list, &d_ptr->option);
			break;
		case D3Scatter:
			DataProcess::dataForScatter3D(list, &d_ptr->option);
			break;
		default:
			break;
		}
	};
	//run data process function concurrently
	QtConcurrent::run(processAndFeedDataConcurrently, dataList);
}





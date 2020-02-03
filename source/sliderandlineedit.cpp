#include "header/sliderandlineedit.h"
#include <QDebug>

void LineEdit::setLineEditStr(const int val)
{
	const QString& str = QString::number(val);
	this->setText(str);
}
void Slider::setSliderValue(const QString& str)
{
	const int val = str.toInt();
	this->setValue(val);
}
void PushButton::setColor(const QColor& color)
{
	//covert QColor to QString.
	const QString& colstr = color.name();
	//set button color with styleSheet form.
	this->setStyleSheet("background-color:" + colstr);
}
void TreeWidgetItemTool::setChecked(QTreeWidgetItem* item, const int column)
{
	if (item->text(3).isEmpty())
	{
		return;
	}
	const int checked = item->checkState(0);
	switch (checked)
	{
	case Qt::CheckState::Checked:
		item->setCheckState(0, Qt::CheckState::Unchecked);
		break;
	case Qt::CheckState::Unchecked:
		item->setCheckState(0, Qt::CheckState::Checked);
		break;
	}
}

void TreeWidgetItemTool::do_setFreeWidget(QTreeWidgetItem* item)
{
	//get item check status.
	bool checked = (item->checkState(0) == Qt::CheckState::Checked);
	//get parent widget.
	QTreeWidget* parentWidget = item->treeWidget();

	for (int i = 1; i < parentWidget->columnCount(); ++i)
	{
		QWidget* w = parentWidget->itemWidget(item, i);
		if (w)
		{
			w->setEnabled(checked);
		}
	}
}



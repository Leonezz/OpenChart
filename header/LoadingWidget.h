#pragma once
#include <QLabel>
#include <QMovie>
class LoadingWidget :public QLabel
{
	Q_OBJECT
public:
	explicit LoadingWidget(QWidget* parent = nullptr);
};


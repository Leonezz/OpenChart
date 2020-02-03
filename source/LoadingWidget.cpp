#include "header/LoadingWidget.h"
LoadingWidget::LoadingWidget(QWidget* parent) :
	QLabel(parent)
{
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground);
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->setAlignment(Qt::AlignCenter);
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	QMovie* movie = new QMovie("./Resources/icon/loading.gif");

	this->setMovie(movie);
	movie->start();
	this->show();
}





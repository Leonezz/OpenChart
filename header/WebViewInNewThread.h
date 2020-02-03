#pragma once
#include <QFileDialog>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <qthread.h>
#include <QFrame>
#include <QTime>
#include <QLayout>
#include <qapplication.h>
#include <qeventloop.h>
class WebViewInNewThread :public QThread
{
	Q_OBJECT
public:
	explicit WebViewInNewThread(QObject* parent = nullptr)
		:QThread(parent)
	{
		m_webView = new QWebEngineView();
		m_webView->resize(600, 400);
		QObject::connect(this, &QThread::finished, this, &QObject::deleteLater);
		QObject::connect(QWebEngineProfile::defaultProfile(), &QWebEngineProfile::downloadRequested, 
			this, &WebViewInNewThread::download);
		this->start();
	}
	~WebViewInNewThread();
	QWebEngineView* get()
	{
		return m_webView;
	}
protected:
	virtual void run() override;
signals:
	void loadDone();
public slots:
	void loadPageByUrl(QUrl url);
private slots:
	void download(QWebEngineDownloadItem* item);
private:
	void do_exec();
private:
	QWebEngineView* m_webView;
};







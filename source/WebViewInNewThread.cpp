#include "header/WebViewInNewThread.h"
void WebViewInNewThread::loadPageByUrl(QUrl url)
{
	m_webView->load(url);
}

WebViewInNewThread::~WebViewInNewThread()
{
	this->quit();
	this->wait();
	delete m_webView;
}

void WebViewInNewThread::do_exec()
{
	this->exec();
	//this may move the main event loop to this new thread.
	QApplication::processEvents();
}

void WebViewInNewThread::run()
{
	do_exec();
}

void WebViewInNewThread::download(QWebEngineDownloadItem* download)
{
	Q_ASSERT(download && download->state() == QWebEngineDownloadItem::DownloadRequested);

	QString path = QFileDialog::getSaveFileName(m_webView, tr("Save as"), download->path());
	if (path.isEmpty())
		return;

	download->setPath(path);
	download->accept();
}



#include <QMainWindow>
#include <QWidget>
#include <QDir>
#include <QUrl>
#include <QtNetWork/QHostAddress>
#include <QFileInfo>
#include <QWebChannel>
#include <QWebSocketServer>
#include <QtWidgets/QApplication>

#include "header/openchart.h"
#include "header/brige.h"
#include "header/websocketclientwrapper.h"
#include "header/websockettransport.h"
#include "header/widgetwithtitlebar.h"
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	qRegisterMetaType<QList<QList<QVariant> >>("QList<QList<QVariant> >");

	QFileInfo jsFile(QDir::currentPath() + "Resources/js/qwebchannel.js");
	if (!jsFile.exists())
	{
		QFile::copy(":/qtwebchannel.qwebchannel.js", jsFile.absoluteFilePath());
	}
	//set websocketserver
	QWebSocketServer server(QStringLiteral("myServer"), QWebSocketServer::NonSecureMode);
	if (!server.listen(QHostAddress::LocalHost, 12138))
	{
		qFatal("Failed to open web socket server.");
		return 1;
	}
	WebSocketClientWrapper clientWrapper(&server);
	QWebChannel channel;
	QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
		&channel, &QWebChannel::connectTo);

	OPENCHART *mainWindow=new OPENCHART();
	Brige brige(mainWindow);

	channel.registerObject(QStringLiteral("brige"), &brige);
	WidgetWithTitleBar* wid = new WidgetWithTitleBar(mainWindow);
	QObject::connect(wid, &WidgetWithTitleBar::quitSignal, &a, &QApplication::quit);
	wid->setObjectName(QString::fromUtf8("BottomWidget"));
	mainWindow->resize(QSize(1300, 650));
	wid->show();
	return a.exec();
}

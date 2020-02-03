/*
This part of code came from a Qt Demo.
Some connect stuff.
*/

#include "header/websocketclientwrapper.h"
#include "header/websockettransport.h"

#include <QWebSocketServer>


WebSocketClientWrapper::WebSocketClientWrapper(QWebSocketServer *server, QObject *parent)
    : QObject(parent)
    , m_server(server)
{
    connect(server, &QWebSocketServer::newConnection,
            this, &WebSocketClientWrapper::handleNewConnection);
}


void WebSocketClientWrapper::handleNewConnection()
{
    emit clientConnected(new WebSocketTransport(m_server->nextPendingConnection()));
}

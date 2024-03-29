#include "QTMegaListener.h"
#include "QTMegaEvent.h"

#include <QCoreApplication>

using namespace mega;

QTMegaListener::QTMegaListener(MegaApi *megaApi, MegaListener *listener) : QObject()
{
    this->megaApi = megaApi;
	this->listener = listener;
}

QTMegaListener::~QTMegaListener()
{
    this->listener = NULL;
    megaApi->removeListener(this);
}

void QTMegaListener::onRequestStart(MegaApi *api, MegaRequest *request)
{
    QTMegaEvent *event = new QTMegaEvent(api, (QEvent::Type)QTMegaEvent::OnRequestStart);
    event->setRequest(request->copy());
    QCoreApplication::postEvent(this, event, INT_MIN);
}

void QTMegaListener::onRequestFinish(MegaApi *api, MegaRequest *request, MegaError *e)
{
    QTMegaEvent *event = new QTMegaEvent(api, (QEvent::Type)QTMegaEvent::OnRequestFinish);
    event->setRequest(request->copy());
    event->setError(e->copy());
    QCoreApplication::postEvent(this, event, INT_MIN);
}

void QTMegaListener::onRequestUpdate(MegaApi *api, MegaRequest *request)
{
    QTMegaEvent *event = new QTMegaEvent(api, (QEvent::Type)QTMegaEvent::OnRequestUpdate);
    event->setRequest(request->copy());
    QCoreApplication::postEvent(this, event, INT_MIN);
}

void QTMegaListener::onRequestTemporaryError(MegaApi *api, MegaRequest *request, MegaError *e)
{
    QTMegaEvent *event = new QTMegaEvent(api, (QEvent::Type)QTMegaEvent::OnRequestTemporaryError);
    event->setRequest(request->copy());
    event->setError(e->copy());
    QCoreApplication::postEvent(this, event, INT_MIN);
}

void QTMegaListener::onTransferStart(MegaApi *api, MegaTransfer *transfer)
{
    QTMegaEvent *event = new QTMegaEvent(api, (QEvent::Type)QTMegaEvent::OnTransferStart);
    event->setTransfer(transfer->copy());
    QCoreApplication::postEvent(this, event, INT_MIN);
}

void QTMegaListener::onTransferFinish(MegaApi *api, MegaTransfer *transfer, MegaError *e)
{
    QTMegaEvent *event = new QTMegaEvent(api, (QEvent::Type)QTMegaEvent::OnTransferFinish);
    event->setTransfer(transfer->copy());
    event->setError(e->copy());
    QCoreApplication::postEvent(this, event, INT_MIN);
}

void QTMegaListener::onTransferUpdate(MegaApi *api, MegaTransfer *transfer)
{
    QTMegaEvent *event = new QTMegaEvent(api, (QEvent::Type)QTMegaEvent::OnTransferUpdate);
    event->setTransfer(transfer->copy());
    QCoreApplication::postEvent(this, event, INT_MIN);
}

void QTMegaListener::onTransferTemporaryError(MegaApi *api, MegaTransfer *transfer, MegaError *e)
{
    QTMegaEvent *event = new QTMegaEvent(api, (QEvent::Type)QTMegaEvent::OnTransferTemporaryError);
    event->setTransfer(transfer->copy());
    event->setError(e->copy());
    QCoreApplication::postEvent(this, event, INT_MIN);
}

void QTMegaListener::onUsersUpdate(MegaApi *api, UserList *users)
{
    QTMegaEvent *event = new QTMegaEvent(api, (QEvent::Type)QTMegaEvent::OnUsersUpdate);
    event->setUsers(users);
    QCoreApplication::postEvent(this, event, INT_MIN);
}

void QTMegaListener::onNodesUpdate(MegaApi *api, NodeList *nodes)
{
    QTMegaEvent *event = new QTMegaEvent(api, (QEvent::Type)QTMegaEvent::OnNodesUpdate);
    event->setNodes(nodes);
    QCoreApplication::postEvent(this, event, INT_MIN);
}

void QTMegaListener::onReloadNeeded(MegaApi *api)
{
    QTMegaEvent *event = new QTMegaEvent(api, (QEvent::Type)QTMegaEvent::OnReloadNeeded);
    QCoreApplication::postEvent(this, event, INT_MIN);
}

void QTMegaListener::onSyncStateChanged(MegaApi *api)
{
    QTMegaEvent *event = new QTMegaEvent(api, (QEvent::Type)QTMegaEvent::OnSyncStateChanged);
    QCoreApplication::postEvent(this, event, INT_MIN);
}

void QTMegaListener::onSyncFileStateChanged(MegaApi *api, const char *filePath, int newState)
{
    QTMegaEvent *event = new QTMegaEvent(api, (QEvent::Type)QTMegaEvent::OnSyncFileStateChanged);
    event->setFilePath(MegaApi::strdup(filePath));
    event->setNewState(newState);
    QCoreApplication::postEvent(this, event, INT_MIN);
}

void QTMegaListener::customEvent(QEvent *e)
{
    QTMegaEvent *event = (QTMegaEvent *)e;
    switch(event->type())
    {
        case QTMegaEvent::OnRequestStart:
            if(listener) listener->onRequestStart(event->getMegaApi(), event->getRequest());
            break;
        case QTMegaEvent::OnRequestUpdate:
            if(listener) listener->onRequestUpdate(event->getMegaApi(), event->getRequest());
            break;
        case QTMegaEvent::OnRequestFinish:
            if(listener) listener->onRequestFinish(event->getMegaApi(), event->getRequest(), event->getError());
            break;
        case QTMegaEvent::OnRequestTemporaryError:
            if(listener) listener->onRequestTemporaryError(event->getMegaApi(), event->getRequest(), event->getError());
            break;
        case QTMegaEvent::OnTransferStart:
            if(listener) listener->onTransferStart(event->getMegaApi(), event->getTransfer());
            break;
        case QTMegaEvent::OnTransferTemporaryError:
            if(listener) listener->onTransferTemporaryError(event->getMegaApi(), event->getTransfer(), event->getError());
            break;
        case QTMegaEvent::OnTransferUpdate:
            if(listener) listener->onTransferUpdate(event->getMegaApi(), event->getTransfer());
            break;
        case QTMegaEvent::OnTransferFinish:
            if(listener) listener->onTransferFinish(event->getMegaApi(), event->getTransfer(), event->getError());
            break;
        case QTMegaEvent::OnUsersUpdate:
            if(listener) listener->onUsersUpdate(event->getMegaApi(), event->getUsers());
            break;
        case QTMegaEvent::OnNodesUpdate:
            if(listener) listener->onNodesUpdate(event->getMegaApi(), event->getNodes());
            break;
        case QTMegaEvent::OnReloadNeeded:
            if(listener) listener->onReloadNeeded(event->getMegaApi());
            break;
        case QTMegaEvent::OnSyncStateChanged:
            if(listener) listener->onSyncStateChanged(event->getMegaApi());
            break;
        case QTMegaEvent::OnSyncFileStateChanged:
            if(listener) listener->onSyncFileStateChanged(event->getMegaApi(), event->getFilePath(), event->getNewState());
            break;
    }
}

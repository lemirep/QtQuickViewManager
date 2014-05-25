#include "ViewManagement.h"
#include <QDebug>

ViewManagement* ViewManagement::instance = NULL;

ViewManagement::ViewManagement(QObject *parent) : QObject(parent),
    source(QUrl()),
    appEngine(new QQmlApplicationEngine()),
    context(this->appEngine->rootContext()),
    window(Q_NULLPTR)
{
}

ViewManagement::ViewManagement(const QUrl &source, QObject *parent) : QObject(parent),
    source(source),
    appEngine(new QQmlApplicationEngine(source)),
    context(this->appEngine->rootContext())
{
    this->window = qobject_cast<QQuickWindow *>(this->appEngine->rootObjects().at(0));
}

ViewManagement *ViewManagement::getInstance()
{
    if (ViewManagement::instance == NULL)
        ViewManagement::instance = new ViewManagement();
    return ViewManagement::instance;
}

ViewManagement::~ViewManagement()
{
    delete this->appEngine;
}


void ViewManagement::setSource(const QUrl &source)
{
    if (this->source != source)
    {
        this->source = source;
        this->appEngine->load(this->source);
        this->window = qobject_cast<QQuickWindow *>(this->appEngine->rootObjects().at(0));
    }
}


QUrl ViewManagement::getSource() const
{
    return this->source;
}

QQmlContext *ViewManagement::getContext() const
{
    return this->context;
}

QQuickWindow *ViewManagement::getWindow() const
{
    return this->window;
}

void ViewManagement::show()
{
    if (this->window)
        this->window->show();
}

void ViewManagement::showFullScreen()
{
    if (this->window)
        this->window->showFullScreen();
}

void ViewManagement::showMaximized()
{
    if (this->window)
        this->window->showMaximized();
}


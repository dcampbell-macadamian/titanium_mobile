/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiCascadesApp.h"
#include <bb/cascades/Application>
#include <bb/cascades/Container>
#include <bb/cascades/Page>
#include "NativeObject.h"

using namespace bb::cascades;

TiCascadesApp::TiCascadesApp(int& argc, char** argv):
    Application(argc, argv)
{
}

TiCascadesApp::~TiCascadesApp()
{
}
void TiCascadesApp::initializeApp()
{
}

void TiCascadesApp::setScene(NativeObject* mainWindow)
{
    if (mainWindow != NULL)
    {
        AbstractPane* pane = (AbstractPane*)(mainWindow->getNativeHandle());
        if (pane != NULL)
        {
            QObject::connect(pane, SIGNAL(destroyed(QObject*)), this, SLOT(Shutdown(QObject*)));
            Application::setScene(pane);
        }
    }
}

void TiCascadesApp::Shutdown(QObject*)
{
}

bool TiCascadesApp::notify(QObject* receiver, QEvent* event)
{
    return bb::cascades::Application::notify(receiver, event);
}

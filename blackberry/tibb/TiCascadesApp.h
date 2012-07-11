/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TICASCADESAPP_H_
#define TICASCADESAPP_H_

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include <bb/cascades/Application>

class NativeObject;

/*
 * TiCascadesApp
 *
 * Cascades application object
 */

class TiCascadesApp : public bb::cascades::Application
{
    Q_OBJECT

public slots:
    void Shutdown(QObject*);
public:
    TiCascadesApp(int& argc, char** argv);
    virtual ~TiCascadesApp();
    void initializeApp();
    void setScene(NativeObject* mainWindow);
    virtual bool notify(QObject* receiver, QEvent* event);
};

#endif /* TICASCADESAPP_H_ */

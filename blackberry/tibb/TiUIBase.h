/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUIBASE_H_
#define TIUIBASE_H_

#include "TiObject.h"

#ifndef _WIN32
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/Control>
#endif

class TiCascadesApp;

class TiUIBase : public TiObject
{
public:
	virtual void setParametersFromObject(Local<Object> obj);
	virtual bool isUIObject() const;
    virtual NativeObjectFactory* getNativeObjectFactory() const;
    virtual NativeObject* getNativeObject() const;
protected:
    TiUIBase(NativeObjectFactory* nativeObjectFactory,const char* name);
    TiUIBase();
    virtual ~TiUIBase();
    virtual bool canAddMembers() const;
    virtual void setNativeObject(NativeObject* nativeObject);
    virtual void onCreateStaticMembers();
    virtual void onSetProperty(const char* color,Local<Value> value);
    virtual void onSetBackgroundColor(const char* color);
    virtual void onSetColor(const char* color);
	virtual void onSetText(const char* text);
	Persistent<Object> createConfig_;
private:
    static Handle<Value> setBackgroundColor_(void* userContext,
                                             TiObject* caller,
                                             const Arguments& args);
    static Handle<Value> setText_(void* userContext,
                                  TiObject* caller,
                                  const Arguments& args);
    static Handle<Value> add_(void* userContext,
                              TiObject* caller,
                              const Arguments& args);

    NativeObject* nativeObject_;
    NativeObjectFactory* nativeObjectFactory_;
};

#endif /* TIUIBASE_H_ */

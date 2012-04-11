/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TIUILABEL_H_
#define TIUILABEL_H_

#include "TiUIBase.h"

class TiUILabel : public TiUIBase
{
public:
    static TiUILabel* createLabel(NativeObjectFactory* nativeObjectFactory);
    virtual void setParametersFromObject(Local<Object> obj);
protected:
    virtual ~TiUILabel();
    virtual void initializeTiObject(TiObject* parentContext);
    virtual void onSetTextAlign(const char* align);
    virtual void onSetFont(Handle<Object> font);
    virtual void onSetBackgroundColor(const char* color);
private:
    TiUILabel(NativeObjectFactory* nativeObjectFactory);
};

#endif /* TIUILABEL_H_ */

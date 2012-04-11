/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUILabel.h"
#include <string.h>

TiUILabel::TiUILabel(NativeObjectFactory* nativeObjectFactory):
	TiUIBase(nativeObjectFactory,"")
{
}

TiUILabel::~TiUILabel()
{
}

TiUILabel* TiUILabel::createLabel(NativeObjectFactory* nativeObjectFactory)
{
	TiUILabel* obj=new TiUILabel(nativeObjectFactory);
	obj->initializeTiObject(NULL);
	return obj;
}

void TiUILabel::setParametersFromObject(Local<Object> obj)
{
    HandleScope handleScope;
	TiUIBase::setParametersFromObject(obj);
	Local<Value> value;
	char* str;
	value=obj->Get(String::New("textAlign"));
	if(!value.IsEmpty())
	{
        str=getStringFromObject(value,"center");
        onSetTextAlign(str);
        freeString(str);
	}
	value=obj->Get(String::New("font"));
	if(!value.IsEmpty())
	{
	    if(value->IsObject())
	    {
	        Handle<Object> fontObj=Handle<Object>::Cast(value);
	        onSetFont(fontObj);
	    }
	}
}

void TiUILabel::initializeTiObject(TiObject* parentContext)
{
	if(!hasInitialized())
	{
		TiUIBase::initializeTiObject(parentContext);
        NativeObject* obj = getNativeObjectFactory()->createNativeObject(NO_TYPE_LABEL);
        setNativeObject(obj);
        obj->release();
	}
}

void TiUILabel::onSetTextAlign(const char* align)
{
    if((stricmp(align,"center")==0)||
            (atoi(align)==0))
    {

    }
    else if((stricmp(align,"left")==0)||
            (atoi(align)==1))
    {

    }
    else if((stricmp(align,"right")==0)||
            (atoi(align)==2))
    {

    }
}

void TiUILabel::onSetFont(Handle<Object> font)
{
    HandleScope handleScope;
    Local<Value> value;
    char* str;
    value=font->Get(String::New("fontFamily"));
    if(!value.IsEmpty())
    {
        str=getStringFromObject(value,"");
        freeString(str);
    }
    value=font->Get(String::New("fontSize"));
    if(!value.IsEmpty())
    {
        str=getStringFromObject(value,"");
        freeString(str);
    }
    value=font->Get(String::New("fontStyle"));
    if(!value.IsEmpty())
    {
        str=getStringFromObject(value,"");
        freeString(str);
    }
    value=font->Get(String::New("fontWeight"));
    if(!value.IsEmpty())
    {
        str=getStringFromObject(value,"");
        freeString(str);
    }
}

void TiUILabel::onSetBackgroundColor(const char* color)
{
}

/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiUIBase.h"
#include "TiGenericFunctionObject.h"

TiUIBase::TiUIBase()
{
    nativeObjectFactory_ = NULL;
    nativeObject_ = NULL;
}

TiUIBase::~TiUIBase()
{
    if (!createConfig_.IsEmpty())
    {
        createConfig_.Dispose();
    }
    if (nativeObject_ != NULL)
    {
        nativeObject_->release();
        nativeObject_ = NULL;
    }
}

TiUIBase::TiUIBase(NativeObjectFactory* nativeObjectFactory, const char* name)
        : TiObject(name)
{
    nativeObjectFactory_ = nativeObjectFactory;
    nativeObject_ = NULL;
}

bool TiUIBase::isUIObject() const
{
    return true;
}

NativeObjectFactory* TiUIBase::getNativeObjectFactory() const
{
    return nativeObjectFactory_;
}

void TiUIBase::onSetProperty(const char* propertyName, Local<Value> value)
{
    char* str = TiObject::getStringFromObject(value, "");
    if (strcmpi(propertyName, "backgroundColor") == 0)
    {
        onSetBackgroundColor(str);
    }
    else if (strcmpi(propertyName, "text") == 0)
    {
        onSetText(str);
    }
    TiObject::freeString(str);
}

bool TiUIBase::canAddMembers() const
{
    return true;
}

NativeObject* TiUIBase::getNativeObject() const
{
    if (nativeObject_ != NULL)
    {
        nativeObject_->addRef();
    }
    return nativeObject_;
}

void TiUIBase::setNativeObject(NativeObject* nativeObject)
{
    if (nativeObject != NULL)
    {
        nativeObject->addRef();
    }
    if (nativeObject_ != NULL)
    {
        nativeObject_->release();
    }
    nativeObject_ = nativeObject;
}

void TiUIBase::onCreateStaticMembers()
{
    TiObject::onCreateStaticMembers();
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setBackgroundColor", this, setBackgroundColor_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "setText", this, setText_);
    TiGenericFunctionObject::addGenericFunctionToParent(this, "add", this, add_);
}

void TiUIBase::setParametersFromObject(Local<Object> obj)
{
    HandleScope handleScope;
    Local < Value > value;
    char* str;
    value = obj->Get(String::New("backgroundColor"));
    if (!value.IsEmpty())
    {
        str = TiObject::getStringFromObject(value, "#000");
        onSetBackgroundColor(str);
        TiObject::freeString(str);
    }
    value = obj->Get(String::New("color"));
    if (!value.IsEmpty())
    {
        str = TiObject::getStringFromObject(value, "#000");
        onSetColor(str);
        TiObject::freeString(str);
    }
    value = obj->Get(String::New("text"));
    if (!value.IsEmpty())
    {
        str = TiObject::getStringFromObject(value, "");
        onSetText(str);
        TiObject::freeString(str);
    }
}

void TiUIBase::onSetBackgroundColor(const char* color)
{
    NativeObject* obj = getNativeObject();
    if (obj != NULL)
    {
        obj->setBackgroundColor(color);
        obj->release();
    }
}

void TiUIBase::onSetText(const char* text)
{
    NativeObject* obj = getNativeObject();
    obj->setText(text);
    obj->release();
}

void TiUIBase::onSetColor(const char* color)
{
    NativeObject* obj = getNativeObject();
    obj->setColor(color);
    obj->release();
}

Handle<Value> TiUIBase::setBackgroundColor_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIBase* obj = (TiUIBase*) userContext;
    if (args.Length() < 1)
    {
        // TODO: throw an exception
        return Undefined();
    }
    if (args[0]->IsString())
    {
        Handle < String > colStr = Handle < String > ::Cast(args[0]);
        String::Utf8Value utfColStr(colStr);
        const char* c = (const char*) (*utfColStr);
        obj->onSetBackgroundColor(c);
    }
    else
    {
        // TODO: throw an exception
        return Undefined();
    }
    return Undefined();
}

Handle<Value> TiUIBase::setText_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIBase* obj = (TiUIBase*) userContext;
    if (args.Length() < 1)
    {
        // TODO: throw an exception
        return Undefined();
    }
    char* str;
    str = TiObject::getStringFromObject(args[0], "");
    obj->onSetText(str);
    TiObject::freeString(str);
    return Undefined();
}

Handle<Value> TiUIBase::add_(void* userContext, TiObject* caller, const Arguments& args)
{
    HandleScope handleScope;
    TiUIBase* obj = (TiUIBase*) userContext;
    if ((args.Length() > 0) && (args[0]->IsObject()))
    {
        TiObject* addObj = getTiObjectFromJsObject(args[0]);
        if ((addObj == NULL) || (!addObj->isUIObject()))
        {
            return Undefined();
        }
        TiUIBase* uiObj = (TiUIBase*) addObj;
        NativeObject* childNO = uiObj->getNativeObject();
        NativeObject* parentNO = obj->getNativeObject();
        parentNO->addChildNativeObject(childNO);
        childNO->release();
        parentNO->release();
    }
    else
    {
        // TODO: throw exception
    }
    return Undefined();
}

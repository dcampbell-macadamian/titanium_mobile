/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeObject.h"
#include <stdio.h>

NativeObject::NativeObject()
{
    refCount_ = 1;
}

NativeObject::~NativeObject()
{
}

void NativeObject::addRef()
{
    refCount_++;
}

void NativeObject::release()
{
    refCount_--;
    if (refCount_ == 0)
    {
        delete this;
    }
}

int NativeObject::setColor(const char* color)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::setBackgroundColor(const char* color)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::setBackgroundImage(const char* image)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::setText(const char* text)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::setFont(const char* family, const char* fontSize, const char* fontStyle, const char* fontWeigth)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::addChildNativeObject(NativeObject* obj)
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

int NativeObject::initialize()
{
    return NATIVE_ERROR_OK;
}

NAHANDLE NativeObject::getNativeHandle() const
{
    return NULL;
}

int NativeObject::open()
{
    return NATIVE_ERROR_NOTSUPPORTED;
}

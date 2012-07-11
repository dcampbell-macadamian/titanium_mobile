/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TiBase.h"

static int g_refCount = 0;

TiBase::TiBase()
{
    refCount_ = 1;
    g_refCount++;
}

TiBase::~TiBase()
{
}

void TiBase::addRef()
{
    // TODO: protect this in a multi-threaded environment
    refCount_++;
    g_refCount++;
}

void TiBase::release()
{
    // TODO: protect this in a multi-threaded environment
    g_refCount--;
    if ((--refCount_) < 1)
    {
        delete this;
    }
}

int TiBase::getGlobalRefCount()
{
    return g_refCount;
}

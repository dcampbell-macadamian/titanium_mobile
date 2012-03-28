/*
 * TiTitaniumObject.cpp
 *
 *  Created on: 2012-03-29
 *      Author: dcampbell
 */

#include "TiTitaniumObject.h"

TiTitaniumObject::TiTitaniumObject()
        : TiObject("Titanium")
{
}

TiTitaniumObject::~TiTitaniumObject()
{
}

TiObject* TiTitaniumObject::createObject()
{
    return new TiTitaniumObject;
}

void TiTitaniumObject::onAddFunctions(void* handle)
{
    addFunction(handle, "include", tiFunction_include);
}

Handle<Value> TiTitaniumObject::tiFunction_include(TiObject* obj,
                                                   const Arguments& args)
{
    return Undefined();
}

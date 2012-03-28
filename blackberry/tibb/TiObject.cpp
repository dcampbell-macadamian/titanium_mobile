/*
 * TiObject.cpp
 *
 *  Created on: 2012-03-28
 *      Author: dcampbell
 */

#include "TiObject.h"
#include <malloc.h>

TiObject::TiObject()
{
    refCount_ = 1;
    name_ = NULL;
    context_ = NULL;
    functionEntry_ = NULL;
    functions_ = 0;
}

TiObject::TiObject(const char* objectName)
{
    name_ = new char[strlen((objectName == NULL) ? "" : objectName) + 1];
    strcpy(name_, (objectName == NULL) ? "" : objectName);
    context_ = NULL;
    functionEntry_ = NULL;
    functions_ = 0;
}

TiObject::~TiObject()
{
    if (name_ != NULL)
    {
        delete[] name_;
        name_ = NULL;
    }
    int i;
    for (i = 0; i < functions_; i++)
    {
        delete functionEntry_[i];
    }
    functions_ = 0;
    if (functionEntry_ != NULL)
    {
        free(functionEntry_);
        functionEntry_ = NULL;
    }
}

void TiObject::addRef()
{
    // TODO: protect in multi-threaded environment
    refCount_++;
}

void TiObject::release()
{
    // TODO: protect in multi-threaded environment
    if ((--refCount_) == 0)
    {
        delete this;
    }
}

void TiObject::initializeTiObject(void* context, TiObject* parentContext)
{
    context_ = context;
    if (parentContext != NULL)
    {
        Persistent<Context>* initContext = (Persistent<Context>*) context;
        HandleScope handleScope;
        Context::Scope contextScope(*initContext);
        template_ = ObjectTemplate::New();
        template_->SetInternalFieldCount(1);
        onAddFunctions(&template_);
        instance_ = template_->NewInstance();
        Handle<External> mapPtr = External::New(this);
        instance_->SetInternalField(0, mapPtr);
    }
}

void TiObject::addChildObject(TiObject* tiObject, const char* objectName)
{
    Persistent<Context>* context = (Persistent<Context>*) getGlobalContext();
    HandleScope handleScope;
    Context::Scope contextScope(*context);
    addProperty(tiObject, NULL);
    template_->Set(String::New(objectName), tiObject->instance_);
    tiObject->initializeTiObject(getGlobalContext(), this);
}

const char* TiObject::getName() const
{
    return name_;
}

void* TiObject::getGlobalContext() const
{
    return context_;
}

Handle<Value> TiObject::onGetValue(Local<String> name, const AccessorInfo& info)
{
    return Undefined();
}

void TiObject::onAddFunctions(void* handle)
{

}

Handle<Value> TiObject::v8OnGetValue_(Local<String> name,
                                      const AccessorInfo& info)
{
    return Undefined();
}

void TiObject::addFunction(void* handle, const char* functionName,
                           FUNC_CALLBACK function)
{
    FUNCTION_ENTRY* funcEntry = addProperty(NULL, function);
    funcEntry->userContext = this;
    Persistent<Context>* context = (Persistent<Context>*) getGlobalContext();
    HandleScope handleScope;
    if (context != NULL)
    {
        Context::Scope contextScope(*context);
        Handle<ObjectTemplate>* temp = (Handle<ObjectTemplate>*) handle;
        Handle<External> callbackPtr = External::New(funcEntry);
        Handle<FunctionTemplate> funcTemp = FunctionTemplate::New(
                v8OnCallFunction_, callbackPtr);
        (*temp)->Set(String::New(functionName), funcTemp);
    }
    else
    {
        Handle<ObjectTemplate>* temp = (Handle<ObjectTemplate>*) handle;
        Handle<External> callbackPtr = External::New(
                functionEntry_[functions_ - 1]);
        Handle<FunctionTemplate> funcTemp = FunctionTemplate::New(
                v8OnCallFunction_, callbackPtr);
        (*temp)->Set(String::New(functionName), funcTemp);
    }
}

Handle<Value> TiObject::v8OnCallFunction_(const Arguments& args)
{
    Handle<External> cbField = Handle<External>::Cast(args.Data());
    FUNCTION_ENTRY* func = (FUNCTION_ENTRY*) cbField->Value();
    return func->cb(func->obj, args);
}

FUNCTION_ENTRY* TiObject::addProperty(TiObject* obj, FUNC_CALLBACK cb)
{
    functions_++;
    functionEntry_ = (FUNCTION_ENTRY**) realloc(
            functionEntry_, sizeof(FUNCTION_ENTRY*) * functions_);
    functionEntry_[functions_ - 1] = new FUNCTION_ENTRY;
    functionEntry_[functions_ - 1]->cb = cb;
    functionEntry_[functions_ - 1]->obj = obj;
    if (obj != NULL)
    {
        obj->addRef();
    }
    return functionEntry_[functions_ - 1];
}

FUNCTION_ENTRY::FUNCTION_ENTRY()
{
    obj = NULL;
    cb = NULL;
    userContext = NULL;
}
FUNCTION_ENTRY::~FUNCTION_ENTRY()
{
    if (obj != NULL)
    {
        obj->release();
    }
}

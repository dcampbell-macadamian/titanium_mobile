/*
 * TiRootObject.cpp
 *
 *  Created on: 2012-03-28
 *      Author: dcampbell
 */

#include "TiRootObject.h"

TiRootObject::TiRootObject(const char* name) :
    TiObject(name)
{
}

TiRootObject::TiRootObject()
{
}

TiRootObject::~TiRootObject()
{
    if(!context_.IsEmpty())
    {
        context_.Dispose();
    }
}

TiObject* TiRootObject::createRootObject()
{
    TiRootObject* obj=new TiRootObject("");
    obj->initializeTiObject(NULL,NULL);
    return obj;
}

void TiRootObject::initializeTiObject(void* context,TiObject* parentObject)
{
    HandleScope scope;
    globalTemplate_ = ObjectTemplate::New();
    globalTemplate_->SetAccessor(String::New("Ti"),v8OnGetValue_);
    globalTemplate_->SetInternalFieldCount(1);
    context_ = Context::New(NULL, globalTemplate_);
    instance_=template_->NewInstance();
    Context::Scope contextScope(context_);
    Handle<External> mapPtr=External::New(this);
    instance_->SetInternalField(0,mapPtr);
}

/*
 *  HandleScope scope;
    template_=ObjectTemplate::New();
    template_->SetInternalFieldCount(1);
    //onAddFunctions(&template_);
    context_=Context::New(NULL,template_,instance_);
    TiObject::initializeTiObject(&context_,NULL);
    Context::Scope contextScope(context_);
    instance_=template_->NewInstance();
    Handle<External> mapPtr=External::New(this);
    instance_->SetInternalField(0,mapPtr);
    instance_->Set(String::New("_test"),Integer::New(27));
 *
 */
Handle<Value> TiRootObject::v8OnGetValue_(Local<String> name, const AccessorInfo& info)
{
    return Undefined();
}

Handle<Value> TiRootObject::tiFunction__debug(TiObject* obj,const Arguments& args)
{
    return Number::New(2.0);
}

Handle<Value> TiRootObject::tiFunction__test(TiObject* obj,const Arguments& args)
{
    return Undefined();
}

void TiRootObject::onAddFunctions(void* handle)
{
    addFunction(handle,"__debug",tiFunction__debug);
    addFunction(handle,"__test",tiFunction__test);

}

/*
 * JavascriptEngine.cpp
 *
 *  Created on: 2012-03-28
 *      Author: dcampbell
 */

#include "JavascriptEngine.h"

JavascriptEngine::JavascriptEngine()
{
}

JavascriptEngine::~JavascriptEngine()
{
    if (!context_.IsEmpty())
    {
        context_.Dispose();
    }
}

int JavascriptEngine::initializeJavascriptEngine()
{
    HandleScope scope;
    Handle<ObjectTemplate> global = ObjectTemplate::New();
    global->SetAccessor(String::New("Titanium"), tiGetterCallback);
    context_ = Context::New(NULL, global);
    return 0;
}

Handle<Value> JavascriptEngine::tiGetterCallback(Local<String> name,
                                                 const AccessorInfo& info)
{
    return Undefined();
}

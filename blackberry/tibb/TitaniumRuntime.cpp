/*
 * TitaniumRuntime.cpp
 *
 *  Created on: 2012-03-28
 *      Author: dcampbell
 */

#include "TitaniumRuntime.h"
#include <stdio.h>
#include <string.h>
#include "TiRootObject.h"
#include "TiTitaniumObject.h"

TitaniumRuntime::TitaniumRuntime()
{
    javaScript_ = NULL;
}

TitaniumRuntime::TitaniumRuntime(const char* javaScript)
{
    javaScript_ = new char[strlen((javaScript == NULL) ? "" : javaScript) + 1];
    strcpy(javaScript_, (javaScript == NULL) ? "" : javaScript);
}

TitaniumRuntime::~TitaniumRuntime()
{
    if (javaScript_ != NULL)
    {
        delete[] javaScript_;
    }
}

int TitaniumRuntime::run(const char* javaScript, int argc, char** argv)
{
    TitaniumRuntime ti(javaScript);
    return ti.internalRun();
}

int TitaniumRuntime::internalRun()
{
    TiObject* obj;
    obj = TiRootObject::createRootObject();
    rootObject_.attachTiObject(obj);
    //obj=TiTitaniumObject::createObject();
    //rootObject_->addChildObject(obj,"Titanium");
    //obj->release();
    //runJavascript("Titanium.include('test');");
    runJavascript("Ti.version");
    return 0;
}

int TitaniumRuntime::runJavascript(const char* script)
{
    Persistent<Context>* context = (Persistent<Context>*) rootObject_
            ->getGlobalContext();
    HandleScope handleScope;
    Context::Scope contextScope(*context);
    TryCatch tryCatch;
    Handle<Script> compile = Script::Compile(String::New(script));
    if (compile.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        Log(*error);
        return -1;
    }
    Handle<Value> result = compile->Run();
    if (result.IsEmpty())
    {
        String::Utf8Value error(tryCatch.Exception());
        Log(*error);
        return -1;
    }
    return 0;
}

void TitaniumRuntime::Log(const char* msg)
{
    fprintf(stderr, "%s\n", msg);
}

/*
 * JavascriptEngine.cpp
 *
 *  Created on: 2012-03-13
 *      Author: dcampbell
 */

#include "JavascriptEngine.h"
#include <stdio.h>

using namespace v8;

JavascriptEngine::JavascriptEngine()
{
	m_isInitialized=0;
}

JavascriptEngine::~JavascriptEngine()
{
	if(m_isInitialized)
	{
		m_context.Dispose();
		m_isInitialized=0;
	}
}

int JavascriptEngine::InitializeScriptEngine()
{
	if(!m_isInitialized)
	{
		m_ti_namespace=FunctionTemplate::New();
		m_ti_namespace->SetClassName(String::New("Titanium"));
		m_ti_prototype=m_ti_namespace->PrototypeTemplate();
		m_instance_pointer=m_ti_namespace->InstanceTemplate();
		m_instance_pointer->SetInternalFieldCount(1);
		m_instance_pointer->SetAccessor(String::New("version"),JS_get_version,NULL);
		//m_template=ObjectTemplate::New();
		//m_template->Set(String::New("print"),FunctionTemplate::New(JS_Print));
		m_context=Context::New();
		m_isInitialized=1;
	}
	return 0;
}

int JavascriptEngine::ExecuteScript(const char* javaScript)
{
	if(!m_isInitialized)
	{
		InitializeScriptEngine();
	}
	Context::Scope context_scope(m_context);
	Handle<Function> ti_ctor=m_ti_namespace->GetFunction();
	Local<Object> obj=ti_ctor->NewInstance();
	m_context->Global()->Set(String::New("Titanium"),obj);
	Handle<String> source=String::New(javaScript);
	Handle<Script> script=Script::Compile(source);
	TryCatch try_catch;
	if(script.IsEmpty())
	{
		String::AsciiValue error(try_catch.Exception());
		if(*error)
		{
			fprintf(stderr,"%s\n",*error);
		}
		return -1;
	}
	v8::Handle<v8::Value> result=script->Run();
	if(result.IsEmpty())
	{
		String::AsciiValue error(try_catch.Exception());
		fprintf(stderr,"%s\n",*error);
		return -1;
	}
	return 0;
}

void JavascriptEngine::OnPrint(const char* text)
{
	fprintf(stderr,"%s\n",text);
}

Handle<Value> JavascriptEngine::JS_Print(const Arguments& args)
{
	bool first=true;
	for(int i=0; i<args.Length(); i++)
	{
		HandleScope handle_scope;
		if(first)
		{
			first=false;
		}
		else
		{
			fprintf(stderr," ");
		}
		String::AsciiValue str(args[i]);
		fprintf(stderr,"%s",*str);
	}
	fprintf(stderr,"\n");
	return Undefined();
}

Handle<Value> JavascriptEngine::JS_get_version(Local<String> property,const AccessorInfo& info)
{
	return Number::New(2.0);
}

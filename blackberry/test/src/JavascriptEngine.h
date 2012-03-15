/*
 * JavascriptEngine.h
 *
 *  Created on: 2012-03-13
 *      Author: dcampbell
 */

#ifndef JAVASCRIPTENGINE_H_
#define JAVASCRIPTENGINE_H_

#include <v8.h>

using namespace v8;

class JavascriptEngine
{
public:
	JavascriptEngine();
	virtual ~JavascriptEngine();
	int InitializeScriptEngine();
	int ExecuteScript(const char* javaScript);
protected:
	virtual void OnPrint(const char* text);
private:
	static Handle<Value> JS_Print(const Arguments& args);
	// Properties
	static Handle<Value> JS_get_buildDate(Local<String> property,const AccessorInfo& info);
	static Handle<Value> JS_get_version(Local<String> property,const AccessorInfo& info);

	int m_isInitialized;
	Handle<FunctionTemplate> m_ti_namespace;
	Handle<ObjectTemplate> m_ti_prototype;
	Handle<ObjectTemplate> m_instance_pointer;
	//v8::Handle<v8::ObjectTemplate> m_template;
	HandleScope m_handle_scope;
	Persistent<Context> m_context;
};

#endif /* JAVASCRIPTENGINE_H_ */

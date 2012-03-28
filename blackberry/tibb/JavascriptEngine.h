/*
 * JavascriptEngine.h
 *
 *  Created on: 2012-03-28
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
    int initializeJavascriptEngine();
private:
    static Handle<Value> tiGetterCallback(Local<String> name,
                                          const AccessorInfo& info);

    Persistent<Context> context_;
};

#endif /* JAVASCRIPTENGINE_H_ */

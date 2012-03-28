/*
 * TitaniumRuntime.h
 *
 *  Created on: 2012-03-28
 *      Author: dcampbell
 */

#ifndef TITANIUMRUNTIME_H_
#define TITANIUMRUNTIME_H_

#include "JavascriptEngine.h"
#include "TiObject.h"
#include "TiObjectScope.h"

class TitaniumRuntime
{
public:
    static int run(const char* javaScript, int argc, char** argv);
private:
    TitaniumRuntime();
    TitaniumRuntime(const char* javaScript);
    virtual ~TitaniumRuntime();
    int internalRun();
    int runJavascript(const char* script);
    void Log(const char* msg);

    char* javaScript_;
    TiObjectScope rootObject_;
};

#endif /* TITANIUMRUNTIME_H_ */

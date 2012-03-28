/*
 * TiRootObject.h
 *
 *  Created on: 2012-03-28
 *      Author: dcampbell
 */

#ifndef TIROOTOBJECT_H_
#define TIROOTOBJECT_H_

#include "TiObject.h"

using namespace std;

struct FUNCTION_ENTRY;

class TiRootObject : public TiObject
{
public:
    static TiObject* createRootObject();
protected:
    virtual ~TiRootObject();
    virtual void initializeTiObject(void* context, TiObject* parentObject);
    virtual void onAddFunctions(void* handle);
private:
    TiRootObject();
    TiRootObject(const char* name);
    static Handle<Value> v8OnGetValue_(Local<String> name,
                                       const AccessorInfo& info);
    static Handle<Value> tiFunction__debug(TiObject* obj,
                                           const Arguments& args);
    static Handle<Value> tiFunction__test(TiObject* obj, const Arguments& args);

    Persistent<Context> context_;
    Handle<ObjectTemplate> globalTemplate_;
};

#endif /* TIROOTOBJECT_H_ */

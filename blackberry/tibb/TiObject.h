/*
 * TiObject.h
 *
 *  Created on: 2012-03-28
 *      Author: dcampbell
 */

#ifndef TIOBJECT_H_
#define TIOBJECT_H_

#include <string.h>
#include <map>
#include <utility>
#include "TiObjectScope.h"

#include <v8.h>

using namespace v8;
using namespace std;

class TiObject;

typedef Handle<Value> (*FUNC_CALLBACK)(TiObject*, const Arguments&);

struct FUNCTION_ENTRY
{
    FUNCTION_ENTRY();
    ~FUNCTION_ENTRY();
    TiObject* obj;
    FUNC_CALLBACK cb;
    void* userContext;
};

class TiObject
{
public:
    TiObject();
    TiObject(const char* objectName);
    virtual ~TiObject();
    void addRef();
    void release();
    virtual void addChildObject(TiObject* tiObject, const char* objectName);
    virtual const char* getName() const;
    virtual void* getGlobalContext() const;
    virtual void addFunction(void* handle, const char* functionName,
                             FUNC_CALLBACK function);
protected:
    virtual void initializeTiObject(void* context, TiObject* parentObject);
    virtual Handle<Value> onGetValue(Local<String> name,
                                     const AccessorInfo& info);
    virtual void onAddFunctions(void* handle);
    Handle<Object> instance_;
    Handle<ObjectTemplate> template_;
    int functions_;
    FUNCTION_ENTRY** functionEntry_;
private:
    void* context_;
    int refCount_;
    char* name_;
    int functionCount_;

    FUNCTION_ENTRY* addProperty(TiObject* obj, FUNC_CALLBACK cb);
    static Handle<Value> v8OnGetValue_(Local<String> name,
                                       const AccessorInfo& info);
    static Handle<Value> v8OnCallFunction_(const Arguments& args);
};

#endif /* TIOBJECT_H_ */

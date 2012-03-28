/*
 * TiTitaniumObject.h
 *
 *  Created on: 2012-03-29
 *      Author: dcampbell
 */

#ifndef TITITANIUMOBJECT_H_
#define TITITANIUMOBJECT_H_

#include "TiObject.h"

class TiTitaniumObject : public TiObject
{
public:
    static TiObject* createObject();
protected:
    virtual ~TiTitaniumObject();
    virtual void onAddFunctions(void* handle);
private:
    TiTitaniumObject();
    static Handle<Value> tiFunction_include(TiObject* obj,
                                            const Arguments& args);
};

#endif /* TITITANIUMOBJECT_H_ */

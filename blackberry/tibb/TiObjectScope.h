/*
 * TiObjectScope.h
 *
 *  Created on: 2012-03-28
 *      Author: dcampbell
 */

#ifndef TIOBJECTSCOPE_H_
#define TIOBJECTSCOPE_H_

class TiObject;

class TiObjectScope
{
public:
    TiObjectScope();
    TiObjectScope(TiObject* obj);
    TiObjectScope(const TiObjectScope& scope);
    virtual ~TiObjectScope();
    const TiObjectScope& operator =(const TiObjectScope& scope);
    operator TiObject*() const;
    TiObject* operator ->() const;
    void attachTiObject(TiObject* obj);
    TiObject* detachTiObject();
private:
    TiObject* object_;
};

#endif /* TIOBJECTSCOPE_H_ */

/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVEOBJECT_H_
#define NATIVEOBJECT_H_

typedef void* NAHANDLE;

#define NATIVE_ERROR_OK                 0
#define NATIVE_ERROR_NOTSUPPORTED       1
#define NATIVE_ERROR_OUTOFMEMORY        2

#define NO_TYPE_CONTAINER               1
#define NO_TYPE_WINDOW                  2
#define NO_TYPE_LABEL                   3

class NativeObjectFactory;

class NativeObject
{
public:
    virtual void addRef();
    virtual void release();
    virtual int getObjectType() const=0;
    virtual int setColor(const char* color);
    virtual int setBackgroundColor(const char* color);
    virtual int setBackgroundImage(const char* image);
    virtual int setText(const char* text);
    virtual int setFont(const char* family, const char* fontSize, const char* fontStyle, const char* fontWeigth);
    virtual int addChildNativeObject(NativeObject* obj);
    virtual NAHANDLE getNativeHandle() const;
    virtual int open();
protected:
    NativeObject();
    virtual ~NativeObject();
    virtual int initialize();
    friend class NativeObjectFactory;
private:
    int refCount_;
};

#endif /* NATIVEOBJECT_H_ */

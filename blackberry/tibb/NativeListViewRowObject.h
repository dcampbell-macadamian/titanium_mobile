/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef NATIVELISTVIEWROWOBJECT_H_
#define NATIVELISTVIEWROWOBJECT_H_

#include "NativeControlObject.h"
#include <bb/cascades/Container>
#include <bb/cascades/ListItemListener>

namespace bb
{
namespace cascades
{
class Container;
class ImageView;
class Label;
}
}

class TiListViewRow;

class NativeListViewRowObject: public NativeControlObject
{
public:
    static NativeListViewRowObject* createListViewRow();
    virtual int getObjectType() const;
    virtual int initialize();
    virtual int setLeftImage(TiObject* obj);
    virtual int setRightImage(TiObject* obj);
    virtual int setTitle(TiObject* obj);
protected:
    virtual ~NativeListViewRowObject();
private:
    NativeListViewRowObject();
    // Disable copy ctor & assignment operator
    NativeListViewRowObject(const NativeListViewRowObject& obj);
    NativeListViewRowObject& operator=(const NativeListViewRowObject& obj);

    bb::cascades::Container* row_;
    bb::cascades::Label* label_;
    bb::cascades::ImageView* leftImage_;
    bb::cascades::ImageView* rightImage_;
};

class TiListViewRow: public bb::cascades::Container,
    public bb::cascades::ListItemListener
{
    Q_OBJECT
public:
    TiListViewRow(bb::cascades::Container* parent = NULL);
    void updateItem(const QString text, const QString imagePath);
    void select(bool select);
    void reset(bool selected, bool activated);
    void activate(bool activate);
};

#endif /* NATIVELISTVIEWROWOBJECT_H_ */

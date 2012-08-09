/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeListViewRowObject.h"
#include "NativeControlObject.h"
#include <bb/cascades/Container>
#include <bb/cascades/StackLayout>
#include <bb/cascades/StackLayoutProperties>
#include <bb/cascades/LayoutDirection>
#include <bb/cascades/DockLayout>
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/HorizontalAlignment>
#include <bb/cascades/VerticalAlignment>
#include <bb/cascades/Label>
#include <bb/cascades/Color>
#include <bb/cascades/Image>
#include <bb/cascades/ImageView>

NativeListViewRowObject::NativeListViewRowObject():
    row_(NULL),
    label_(NULL),
    leftImage_(NULL),
    rightImage_(NULL)
{
}

NativeListViewRowObject::~NativeListViewRowObject()
{
}

NativeListViewRowObject* NativeListViewRowObject::createListViewRow()
{
    return new NativeListViewRowObject;
}

int NativeListViewRowObject::getObjectType() const
{
    return N_TYPE_LIST_VIEW_ROW;
}

int NativeListViewRowObject::initialize()
{
    row_ = new bb::cascades::Container();
    bb::cascades::StackLayout* layout = new bb::cascades::StackLayout();
    layout->setLayoutDirection(bb::cascades::LayoutDirection::LeftToRight);
    row_->setLayout(layout);
    row_->setPreferredWidth(2000.0f);
    setControl(row_);
    return NATIVE_ERROR_OK;
}

int NativeListViewRowObject::setLeftImage(TiObject* obj)
{
    Q_ASSERT(row_ != NULL);
    QString source;
    int error = NativeControlObject::getString(obj, source);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    QUrl url(source);
    if (leftImage_ == NULL)
    {
        leftImage_ = new bb::cascades::ImageView();
        row_->insert(0, leftImage_);
    }
    leftImage_->setImage(bb::cascades::Image(url));
    return NATIVE_ERROR_OK;
}

int NativeListViewRowObject::setRightImage(TiObject* obj)
{
    Q_ASSERT(row_ != NULL);
    QString source;
    int error = NativeControlObject::getString(obj, source);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    QUrl url(source);
    if (rightImage_ == NULL)
    {
        rightImage_ = new bb::cascades::ImageView();
        row_->add(rightImage_);
    }
    rightImage_->setImage(bb::cascades::Image(url));
    return NATIVE_ERROR_OK;
}

int NativeListViewRowObject::setTitle(TiObject* obj)
{
    QString title;
    int error = NativeControlObject::getString(obj, title);
    if (error != NATIVE_ERROR_OK)
    {
        return error;
    }
    if (label_ == NULL)
    {
        label_ = bb::cascades::Label::create();
        if (leftImage_ == NULL)
        {
            row_->insert(0, label_);
        }
        else
        {
            row_->insert(1, label_);
        }
    }
    label_->setText(title);
    return NATIVE_ERROR_OK;
}

// TiListViewRow

TiListViewRow::TiListViewRow(bb::cascades::Container* parent):
    bb::cascades::Container(parent)
{
}

void TiListViewRow::updateItem(const QString text, const QString imagePath)
{
}

void TiListViewRow::select(bool select)
{
    bb::cascades::Container* container = (bb::cascades::Container*)at(0);
    if (select)
    {
        container->setBackground(bb::cascades::Color::fromRGBA(0.5f, 0.5f, 1.0f, 1.0f));
    }
    else
    {
        container->setBackground(bb::cascades::Color::White);
    }
}

void TiListViewRow::reset(bool selected, bool activated)
{
    select(selected);
    activate(activated);
}

void TiListViewRow::activate(bool activate)
{
    if (activate)
    {
        setOpacity(1.0);
    }
    else
    {
        setOpacity(0.5);
    }
}

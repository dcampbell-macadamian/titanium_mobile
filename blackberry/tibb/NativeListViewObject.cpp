/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2009-2012 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "NativeListViewObject.h"

#include <bb/cascades/Container>
#include <bb/cascades/DataModel>
#include <bb/cascades/Image>
#include <bb/cascades/ImageView>
#include <bb/cascades/ListView>
#include <bb/cascades/QListDataModel>
#include <bb/cascades/Label>
#include <bb/cascades/ListItemManager>
#include <bb/cascades/VisualNode>
#include <bb/cascades/DockLayout>
#include <bb/cascades/DockLayoutProperties>
#include <bb/cascades/HorizontalAlignment>
#include <bb/cascades/VerticalAlignment>
#include "NativeListViewObject.h"
#include "PersistentV8Value.h"
#include "TiEventContainerFactory.h"
#include "TiObject.h"
#include "NativeListViewRowObject.h"

NativeListViewObject::NativeListViewObject()
{
    listView_ = NULL;
    top_ = 0;
    left_ = 0;
}

NativeListViewObject::~NativeListViewObject()
{
}

NativeListViewObject* NativeListViewObject::createListView()
{
    return new NativeListViewObject;
}

int NativeListViewObject::initialize()
{
    listView_ = bb::cascades::ListView::create();
    setControl(listView_);
    listView_->setListItemManager(new ListViewItemFactory());
    return NATIVE_ERROR_OK;
}

int NativeListViewObject::setData(TiObject* obj)
{
    QVector<QVariant> dataModel;
    int error = NativeControlObject::getDataModel(obj, dataModel);
    if (!N_SUCCEEDED(error))
    {
        return error;
    }
    QList<QVariant> dataList;
    for (int i = 0; i < dataModel.size(); ++i)
    {
        dataList.append(dataModel[i]);
    }
    listView_->setDataModel(new bb::cascades::QListDataModel<QVariant>(dataList));
    return NATIVE_ERROR_OK;
}

int NativeListViewObject::getObjectType() const
{
    return N_TYPE_LIST_VIEW;
}

NAHANDLE NativeListViewObject::getNativeHandle() const
{
    return listView_;
}

QVariant NativeListViewObject::getListViewElementFromIndex(QVariantList var)
{
    bb::cascades::DataModel* dataM = listView_->dataModel();
    QVariant property = dataM->data(var);
    return property;
}

int NativeListViewObject::scrollToIndex(int index)
{
    QVariant variant(index);
    QVariantList scroll;
    scroll.append(variant);
    listView_->scrollToItem(scroll);
    return NATIVE_ERROR_OK;
}

void NativeListViewObject::setupEvents(TiEventContainerFactory* containerFactory)
{
    NativeControlObject::setupEvents(containerFactory);
    TiEventContainer* eventClicked = containerFactory->createEventContainer();
    eventClicked->setDataProperty("type", tetCLICK);
    events_.insert(tetCLICK, EventPairSmartPtr(eventClicked, new ListViewEventHandler(eventClicked, this)));
    QObject::connect(listView_, SIGNAL(selectionChanged(QVariantList, bool)), events_[tetCLICK]->handler, SLOT(selectionChanged(QVariantList, bool)));
}

/*********** ListViewItemFactory class *************/
bb::cascades::VisualNode* ListViewItemFactory::createItem(bb::cascades::ListView*, const QString&)
{
    TiListViewRow* row = new TiListViewRow();
    row->setBackground(bb::cascades::Color::LightGray);
    row->setLayout(new bb::cascades::DockLayout());
    bb::cascades::DockLayoutProperties* properties = bb::cascades::DockLayoutProperties::create();
    properties->setHorizontalAlignment(bb::cascades::HorizontalAlignment::Fill);
    properties->setVerticalAlignment(bb::cascades::VerticalAlignment::Center);
    row->setLayoutProperties(properties);
    row->setPreferredWidth(2000.0f);
    row->setBottomMargin(1.0f);
    return row;
}

void ListViewItemFactory::updateItem(bb::cascades::ListView*, bb::cascades::VisualNode* listItem, const QString&,
                                     const QVariantList&, const QVariant& data)
{
    // Trying to parse the title from v8 object
    if (data.canConvert<PersistentV8Value>())
    {
        PersistentV8Value v8Value = data.value<PersistentV8Value>();
        Persistent<Value> propValue = v8Value.getValue();
        if (propValue->IsObject())
        {
            TiListViewRow* row = (TiListViewRow*)listItem;
            row->removeAll();
            TiObject* tiObj = TiObject::getTiObjectFromJsObject(propValue);
            NativeObject* nObj = NULL;
            if (tiObj != NULL)
            {
                nObj = tiObj->getNativeObject();
            }
            if (nObj == NULL)
            {
                Local<Value> titleValue = propValue->ToObject()->Get(String::New("title"));
                Local<String> valueStr = titleValue->ToString();
                String::Utf8Value valueUTF(valueStr);
                bb::cascades::Label* label = bb::cascades::Label::create();
                label->setText(QString(*valueUTF));
                Local<Value> leftImage = propValue->ToObject()->Get(String::New("leftImage"));
                if (!leftImage->IsUndefined())
                {
                    String::Utf8Value leftImageStrUTF(leftImage->ToString());
                    bb::cascades::ImageView* leftImageView = new bb::cascades::ImageView();
                    leftImageView->setImage(bb::cascades::Image(QString(*leftImageStrUTF)));
                    row->add(leftImageView);
                }
                row->add(label);
                Local<Value> rightImage = propValue->ToObject()->Get(String::New("rightImage"));
                if (!rightImage->IsUndefined())
                {
                    String::Utf8Value rightImageStrUTF(rightImage->ToString());
                    bb::cascades::ImageView* rightImageView = new bb::cascades::ImageView();
                    rightImageView->setImage(bb::cascades::Image(QString(*rightImageStrUTF)));
                    row->add(rightImageView);
                }
            }
            else
            {
                row->add((bb::cascades::Control*)nObj->getNativeHandle());
                nObj->release();
            }
        }
    }
}

/*********** ListViewEventHandler class *************/
void ListViewEventHandler::selectionChanged(QVariantList var, bool)
{
    eventContainer_->setDataProperty("index", var[0].toString().toStdString().c_str());
    Persistent<Value> propValue;
    if (owner_)
    {
        QVariant property = owner_->getListViewElementFromIndex(var);
        if (property.canConvert<PersistentV8Value>())
        {
            PersistentV8Value v8Value = property.value<PersistentV8Value>();
            propValue = v8Value.getValue();
        }
    }
    eventContainer_->setV8ValueProperty("rowData", propValue);
    eventContainer_->fireEvent();
}

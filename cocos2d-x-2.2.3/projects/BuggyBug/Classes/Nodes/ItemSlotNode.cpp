//
//  ItemSlotNode.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-19.
//
//

#include "ItemSlotNode.h"
#include "UITools.h"
#include "AllDefines.h"
#include "StoreScene.h"
#include "DBUtil.h"
#include "UILoaderItem.h"
#include "structDef.h"
#include "ConfigCache.h"
ItemSlotNode::ItemSlotNode(void)
{
	this->ignoreAnchorPointForPosition(false);
}


ItemSlotNode::~ItemSlotNode(void)
{
    
}

bool ItemSlotNode::init()
{
    currIndex = 1;
    itemSprite1 = NULL;
    itemSprite2 = NULL;
    itemSprite3 = NULL;
	return true;
}

ItemSlotNode* ItemSlotNode::create( const char *bgImg )
{
    UITouchSprite *sprite = UITouchSprite::create(bgImg,bgImg);
	return ItemSlotNode::create(sprite);
}

ItemSlotNode* ItemSlotNode::create( UITouchSprite *bgSprite )
{
	ItemSlotNode *node = new ItemSlotNode;
	node->initWithSprite(bgSprite);
	node->autorelease();
	return node;
}

ItemSlotNode* ItemSlotNode::create( CCSize &size )
{
	ItemSlotNode *node = new ItemSlotNode;
	node->initWithSize(size);
	node->autorelease();
	return node;
}

void ItemSlotNode::setBackground( UITouchSprite *bgSprite )
{
    bgSprite->setPosition(ccp(bgSprite->getContentSize().width * .5,bgSprite->getContentSize().height *.5));
    bgSprite->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ItemSlotNode::downaAction)));
    bgSprite->setTouchEnabled(true);
	this->addChild(bgSprite);
	m_bgSprite = bgSprite;
    
    lastBut = UITouchSprite::create("slot-left-arrow.png", "slot-left-arrow.png");
    lastBut->setTag(100);
    lastBut->setPosition(ccp(bgSprite->getContentSize().width* 0.34, bgSprite->getContentSize().height -bgSprite->getContentSize().height-20));
    lastBut->setTouchEnabled(true);
    lastBut->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ItemSlotNode::lastAction)));
    this->addChild(lastBut);
    
    nextBut = UITouchSprite::create("slot-right-arrow.png", "slot-right-arrow.png");
    nextBut->setTag(100);
    nextBut->setPosition(ccp(bgSprite->getContentSize().width* 0.7, bgSprite->getContentSize().height -bgSprite->getContentSize().height-20));
    nextBut->setTouchEnabled(true);
    nextBut->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ItemSlotNode::nextAction)));
    this->addChild(nextBut);
}

bool ItemSlotNode::initWithSprite( UITouchSprite *sprite )
{
	CCSize size = sprite->getContentSize();
    size.height = size.height+67;
	setBackground(sprite);
	return initWithSize(size);
}

bool ItemSlotNode::initWithSize( CCSize &size )
{
	this->setAnchorPoint(ccp(.5,.5));
	this->setContentSize(size);
    
	return init();
}

void ItemSlotNode::lastAction(CCNode *node)
{
    if (currIndex>1) {
        currIndex = currIndex-1;
    }else{
        currIndex = 3;
    }
    this->showWeapon(currIndex);
}

void ItemSlotNode::nextAction(CCNode *node)
{
    if (currIndex<3) {
        currIndex = currIndex+1;
    }else{
        currIndex = 1;
    }
    this->showWeapon(currIndex);
}

void ItemSlotNode::loadEquipWeapon(CCArray *itemArray)
{
    UILoaderItem *itemLoader = (UILoaderItem*)ConfigCache::sharedConfigCache()->getConfig(xml_type_item);
    for (int i=0; i<itemArray->count(); i++) {
        CCDictionary *dic = (CCDictionary*)itemArray->objectAtIndex(i);
        CCString *idstr = (CCString*)dic->objectForKey("id");
        CCString *typestr = (CCString*)dic->objectForKey("type");
        CCString *numberstr = (CCString*)dic->objectForKey("number");
        CCString *equipslotindexstr = (CCString*)dic->objectForKey("equipSlotIndex");
        
        ItemPropertyStruct itemIt = itemLoader->getProperty(typestr->intValue(),idstr->intValue());
        itemIt.number = numberstr->intValue();
        
        switch (equipslotindexstr->intValue()) {
            case 1:
                itemInfo1=itemIt;
                itemSprite1 = UITools::createSprite(itemInfo1.imageFile.c_str());
                itemSprite1->setScale(1.3);
                itemSprite1->setPosition(ccp(m_bgSprite->getContentSize().width * .53,m_bgSprite->getContentSize().height *.44));
                m_bgSprite->addChild(itemSprite1);
                this->showWeapon(currIndex);
                break;
            case 2:
                itemInfo2=itemIt;
                itemSprite2 = UITools::createSprite(itemInfo2.imageFile.c_str());
                itemSprite2->setScale(1.3);
                itemSprite2->setPosition(ccp(m_bgSprite->getContentSize().width * .53,m_bgSprite->getContentSize().height *.44));
                m_bgSprite->addChild(itemSprite2);
                this->showWeapon(currIndex);
                break;
            case 3:
                itemInfo3=itemIt;
                itemSprite3 = UITools::createSprite(itemInfo3.imageFile.c_str());
                itemSprite3->setScale(1.3);
                itemSprite3->setPosition(ccp(m_bgSprite->getContentSize().width * .53,m_bgSprite->getContentSize().height *.44));
                m_bgSprite->addChild(itemSprite3);
                this->showWeapon(currIndex);
                break;
            default:
                break;
        }
    }
}

void ItemSlotNode::equipWeapon(ItemPropertyStruct itemInfo)
{
    switch (currIndex) {
        case 1:
            if (itemSprite1) {
                DBUtil::initDB("MyGameInfo.db");
                std::string updateNumberSql = "delete from my_item where itemid = "+CCString::createWithFormat("%d",itemInfo1.id)->m_sString+" and type = "+CCString::createWithFormat("%d",itemInfo1.type)->m_sString+";";
                DBUtil::deleteData(updateNumberSql);
                DBUtil::closeDB();
                
                StoreScene *sc = (StoreScene*)m_storeScene;
                sc->stNode->addItem(itemInfo1);
                
                itemSprite1->removeFromParent();
            }
            itemInfo1=itemInfo;
            itemSprite1 = UITools::createSprite(itemInfo1.imageFile.c_str());
            itemSprite1->setScale(1.3);
            itemSprite1->setPosition(ccp(m_bgSprite->getContentSize().width * .53,m_bgSprite->getContentSize().height *.44));
            m_bgSprite->addChild(itemSprite1);
            this->showWeapon(currIndex);
        {
            DBUtil::initDB("MyGameInfo.db");
            std::string updateNumberSql = "update my_item set equipSlotIndex = "+CCString::createWithFormat("%d",1)->m_sString+" where itemid = "+CCString::createWithFormat("%d",itemInfo1.id)->m_sString+" and type = "+CCString::createWithFormat("%d",itemInfo1.type)->m_sString+";";
            DBUtil::updateData(updateNumberSql);
            DBUtil::closeDB();
        }
            
            break;
        case 2:
            if (itemSprite2) {
                DBUtil::initDB("MyGameInfo.db");
                std::string updateNumberSql = "delete from my_item where itemid = "+CCString::createWithFormat("%d",itemInfo2.id)->m_sString+" and type = "+CCString::createWithFormat("%d",itemInfo2.type)->m_sString+";";
                DBUtil::deleteData(updateNumberSql);
                DBUtil::closeDB();
                
                StoreScene *sc = (StoreScene*)m_storeScene;
                sc->stNode->addItem(itemInfo2);
                
                itemSprite2->removeFromParent();
            }
            itemInfo2=itemInfo;
            itemSprite2 = UITools::createSprite(itemInfo2.imageFile.c_str());
            itemSprite2->setScale(1.3);
            itemSprite2->setPosition(ccp(m_bgSprite->getContentSize().width * .53,m_bgSprite->getContentSize().height *.44));
            m_bgSprite->addChild(itemSprite2);
            this->showWeapon(currIndex);
        {
            DBUtil::initDB("MyGameInfo.db");
            std::string updateNumberSql = "update my_item set equipSlotIndex = "+CCString::createWithFormat("%d",2)->m_sString+" where itemid = "+CCString::createWithFormat("%d",itemInfo2.id)->m_sString+" and type = "+CCString::createWithFormat("%d",itemInfo2.type)->m_sString+";";
            DBUtil::updateData(updateNumberSql);
            DBUtil::closeDB();
        }
            break;
        case 3:
            
            if (itemSprite3)
            {
                DBUtil::initDB("MyGameInfo.db");
                std::string updateNumberSql = "delete from my_item where itemid = "+CCString::createWithFormat("%d",itemInfo3.id)->m_sString+" and type = "+CCString::createWithFormat("%d",itemInfo3.type)->m_sString+";";
                DBUtil::deleteData(updateNumberSql);
                DBUtil::closeDB();
                
                StoreScene *sc = (StoreScene*)m_storeScene;
                sc->stNode->addItem(itemInfo3);
                
                itemSprite3->removeFromParent();
            }
            itemInfo3=itemInfo;
            itemSprite3 = UITools::createSprite(itemInfo3.imageFile.c_str());
            itemSprite3->setScale(1.3);
            itemSprite3->setPosition(ccp(m_bgSprite->getContentSize().width * .53,m_bgSprite->getContentSize().height *.44));
            m_bgSprite->addChild(itemSprite3);
            this->showWeapon(currIndex);
        {
            DBUtil::initDB("MyGameInfo.db");
            std::string updateNumberSql = "update my_item set equipSlotIndex = "+CCString::createWithFormat("%d",3)->m_sString+" where itemid = "+CCString::createWithFormat("%d",itemInfo3.id)->m_sString+" and type = "+CCString::createWithFormat("%d",itemInfo3.type)->m_sString+";";
            DBUtil::updateData(updateNumberSql);
            DBUtil::closeDB();
        }
            break;
        default:
            break;
    }
}

void ItemSlotNode::showWeapon(int index)
{
    switch (index) {
        case 1:
            currItemInfo=itemInfo1;
            if (itemSprite1) {
                itemSprite1->setVisible(true);
            }
            if (itemSprite2) {
                itemSprite2->setVisible(false);
            }
            if (itemSprite3) {
                itemSprite3->setVisible(false);
            }
            break;
        case 2:
            currItemInfo=itemInfo2;
            if (itemSprite1) {
                itemSprite1->setVisible(false);
            }
            if (itemSprite2) {
                itemSprite2->setVisible(true);
            }
            if (itemSprite3) {
                itemSprite3->setVisible(false);
            }
            break;
        case 3:
            currItemInfo=itemInfo3;
            if (itemSprite1) {
                itemSprite1->setVisible(false);
            }
            if (itemSprite2) {
                itemSprite2->setVisible(false);
            }
            if (itemSprite3) {
                itemSprite3->setVisible(true);
            }
            break;
        default:
            break;
    }
}

void ItemSlotNode::downaAction(CCNode *node)
{
    CCLog("点击了！！！");
    DBUtil::initDB("MyGameInfo.db");
    std::string updateNumberSql = "delete from my_item where itemid = "+CCString::createWithFormat("%d",currItemInfo.id)->m_sString+" and type = "+CCString::createWithFormat("%d",currItemInfo.type)->m_sString+";";
    DBUtil::deleteData(updateNumberSql);
    DBUtil::closeDB();
    switch (currIndex) {
        case 1:
            if (itemSprite1) {
                itemSprite1->removeFromParent();
                itemSprite1 = NULL;
                itemInfo1.id=0;
                itemInfo1.type=0;
                itemInfo1.number=0;
                itemInfo1.imageFile="";
                StoreScene *sc = (StoreScene*)m_storeScene;
                sc->stNode->addItem(currItemInfo);
                currItemInfo = itemInfo1;
            }
            break;
        case 2:
            if (itemSprite2) {
                itemSprite2->removeFromParent();
                itemSprite2 = NULL;
                itemInfo2.id=0;
                itemInfo2.type=0;
                itemInfo2.number=0;
                itemInfo2.imageFile="";
                StoreScene *sc = (StoreScene*)m_storeScene;
                sc->stNode->addItem(currItemInfo);
                currItemInfo = itemInfo2;
            }
            break;
        case 3:
            if (itemSprite3) {
                itemSprite3->removeFromParent();
                itemSprite3 = NULL;
                itemInfo3.id=0;
                itemInfo3.type=0;
                itemInfo3.number=0;
                itemInfo3.imageFile="";
                StoreScene *sc = (StoreScene*)m_storeScene;
                sc->stNode->addItem(currItemInfo);
                currItemInfo = itemInfo3;
            }
            break;
        default:
            break;
    }
}

void ItemSlotNode::onEnter()
{
    CCNode::onEnter();
}

void ItemSlotNode::onExit()
{
    CCNode::onExit();
    m_bgSprite->setTouchEnabled(false);
    lastBut->setTouchEnabled(false);
    nextBut->setTouchEnabled(false);
}
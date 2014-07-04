//
//  WeaponSlot.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-6-11.
//
//

#include "WeaponSlot.h"
#include "UITools.h"
#include "AllDefines.h"
#include "StoreScene.h"
#include "DBUtil.h"
#include "UILoaderItem.h"
#include "structDef.h"
#include "ConfigCache.h"
WeaponSlot::WeaponSlot(void)
{
	this->ignoreAnchorPointForPosition(false);
}


WeaponSlot::~WeaponSlot(void)
{
    
}

bool WeaponSlot::init()
{
    currIndex = 1;
    itemSprite1 = NULL;
    itemSprite2 = NULL;
    itemSprite3 = NULL;
	return true;
}

WeaponSlot* WeaponSlot::create( const char *bgImg )
{
    UITouchSprite *sprite = UITouchSprite::create(bgImg,bgImg);
	return WeaponSlot::create(sprite);
}

WeaponSlot* WeaponSlot::create( UITouchSprite *bgSprite )
{
	WeaponSlot *node = new WeaponSlot;
	node->initWithSprite(bgSprite);
	node->autorelease();
	return node;
}

WeaponSlot* WeaponSlot::create( CCSize &size )
{
	WeaponSlot *node = new WeaponSlot;
	node->initWithSize(size);
	node->autorelease();
	return node;
}

void WeaponSlot::setBackground( UITouchSprite *bgSprite )
{
    bgSprite->setPosition(ccp(bgSprite->getContentSize().width * .5,bgSprite->getContentSize().height *.5));
    bgSprite->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(WeaponSlot::downaAction)));
    //bgSprite->m_nPriority = -1300;
    bgSprite->setTouchEnabled(true);
	this->addChild(bgSprite);
	m_bgSprite = bgSprite;
}

bool WeaponSlot::initWithSprite( UITouchSprite *sprite )
{
	CCSize size = sprite->getContentSize();
    //size.height = size.height+67;
	setBackground(sprite);
	return initWithSize(size);
}

bool WeaponSlot::initWithSize( CCSize &size )
{
	this->setAnchorPoint(ccp(.5,.5));
	this->setContentSize(size);
    
	return init();
}


void WeaponSlot::loadEquipWeapon(CCArray *itemArray)
{
    UILoaderItem *itemLoader = (UILoaderItem*)ConfigCache::sharedConfigCache()->getConfig(xml_type_item);
    for (int i=0; i<itemArray->count(); i++) {
        CCDictionary *dic = (CCDictionary*)itemArray->objectAtIndex(i);
        CCString *idstr = (CCString*)dic->objectForKey("id");
        CCString *typestr = (CCString*)dic->objectForKey("type");
        CCString *numberstr = (CCString*)dic->objectForKey("number");
        //CCString *equipslotindexstr = (CCString*)dic->objectForKey("equipSlotIndex");
        
        ItemPropertyStruct itemIt = itemLoader->getProperty(typestr->intValue(),idstr->intValue());
        itemIt.number = numberstr->intValue();
        
        switch (i+1) {
            case 1:
                itemInfo1=itemIt;
                itemSprite1 = UITools::createSprite(itemInfo1.playImage.c_str());
                itemSprite1->setScale(1);
                itemSprite1->setPosition(ccp(m_bgSprite->getContentSize().width * .53,m_bgSprite->getContentSize().height *.46));
                addChild(itemSprite1,-1000);
                //this->showWeapon(currIndex);
                break;
            case 2:
                itemInfo2=itemIt;
                itemSprite2 = UITools::createSprite(itemInfo2.playImage.c_str());
                itemSprite2->setScale(1);
                itemSprite2->setPosition(ccp(m_bgSprite->getContentSize().width * .53,m_bgSprite->getContentSize().height *.46));
                addChild(itemSprite2,-1000);
                //this->showWeapon(currIndex);
                break;
            case 3:
                itemInfo3=itemIt;
                itemSprite3 = UITools::createSprite(itemInfo3.playImage.c_str());
                itemSprite3->setScale(1);
                itemSprite3->setPosition(ccp(m_bgSprite->getContentSize().width * .53,m_bgSprite->getContentSize().height *.46));
                addChild(itemSprite3,-1000);
                //this->showWeapon(currIndex);
                break;
            default:
                break;
        }
    }
    
    if (itemSprite1) {
        currItemInfo=itemInfo1;
        itemSprite1->setVisible(true);
    }
    if (itemSprite2) {
        itemSprite2->setVisible(false);
    }
    if (itemSprite3) {
        itemSprite3->setVisible(false);
    }
    
    if (itemArray->count()==2) {
        indexSpriteOne = UITools::createSprite("HUD_35.png");
        indexSpriteOne->setPosition(ccp(50, -5));
        addChild(indexSpriteOne);
        
        indexSpriteTwo = UITools::createSprite("HUD_37.png");
        indexSpriteTwo->setPosition(ccp(75, -5));
        addChild(indexSpriteTwo);
    }else if(itemArray->count()==3){
        indexSpriteOne = UITools::createSprite("HUD_35.png");
        indexSpriteOne->setPosition(ccp(40, -5));
        addChild(indexSpriteOne);
        
        indexSpriteTwo = UITools::createSprite("HUD_37.png");
        indexSpriteTwo->setPosition(ccp(65, -5));
        addChild(indexSpriteTwo);
        
        indexSpriteThree = UITools::createSprite("HUD_37.png");
        indexSpriteThree->setPosition(ccp(90, -5));
        addChild(indexSpriteThree);
    }
}



void WeaponSlot::showWeapon(int index)
{
    switch (index) {
        case 2:
            if (itemSprite2) {
                itemSprite1->setVisible(false);
                currItemInfo=itemInfo2;
                currIndex = currIndex+1;
                itemSprite2->setVisible(true);
                
                CCTexture2D * text2d = CCTextureCache::sharedTextureCache()->
                addImage("HUD_35.png");
                indexSpriteTwo->setTexture(text2d);
                
                CCTexture2D * text2d2 = CCTextureCache::sharedTextureCache()->
                addImage("HUD_37.png");
                indexSpriteOne->setTexture(text2d2);
            }
            break;
        case 3:
            if (itemSprite3) {
                itemSprite2->setVisible(false);
                currItemInfo=itemInfo3;
                currIndex = currIndex+1;
                itemSprite3->setVisible(true);
                
                CCTexture2D * text2d = CCTextureCache::sharedTextureCache()->
                addImage("HUD_35.png");
                indexSpriteThree->setTexture(text2d);
                
                CCTexture2D * text2d2 = CCTextureCache::sharedTextureCache()->
                addImage("HUD_37.png");
                indexSpriteTwo->setTexture(text2d2);
            }else{
                itemSprite2->setVisible(false);
                currItemInfo=itemInfo1;
                currIndex = 1;
                itemSprite1->setVisible(true);
                
                CCTexture2D * text2d = CCTextureCache::sharedTextureCache()->
                addImage("HUD_35.png");
                indexSpriteOne->setTexture(text2d);
                
                CCTexture2D * text2d2 = CCTextureCache::sharedTextureCache()->
                addImage("HUD_37.png");
                indexSpriteTwo->setTexture(text2d2);
            }
            break;
        case 4:
            if (itemSprite1) {
                itemSprite3->setVisible(false);
                currItemInfo=itemInfo1;
                currIndex = 1;
                itemSprite1->setVisible(true);
                
                CCTexture2D * text2d = CCTextureCache::sharedTextureCache()->
                addImage("HUD_35.png");
                indexSpriteOne->setTexture(text2d);
                
                CCTexture2D * text2d2 = CCTextureCache::sharedTextureCache()->
                addImage("HUD_37.png");
                indexSpriteThree->setTexture(text2d2);
            }
            break;
        default:
            break;
    }
}

void WeaponSlot::downaAction(CCNode *node)
{
    this->showWeapon(currIndex+1);
}
//
//  ItemBuyLayer.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-18.
//
//

#include "ItemBuyLayer.h"
#include "AllDefines.h"
#include "UITools.h"

ItemBuyLayer::ItemBuyLayer(void)
:m_ClickCallback(NULL),
number(0)
{
	this->ignoreAnchorPointForPosition(false);
}


ItemBuyLayer::~ItemBuyLayer(void)
{
}

void ItemBuyLayer::show()
{
	this->setVisible(true);
}

void ItemBuyLayer::hide()
{
	this->runAction(CCFadeTo::create(0.3f , 0));
}

bool ItemBuyLayer::init()
{
    this->setTouchEnabled(true);
    
    CCLayerColor* layerColor = CCLayerColor::create();
    layerColor->setColor(ccc3(0, 0, 0));
    layerColor->setOpacity(200);
    layerColor->setContentSize(CCSizeMake(CCScreenWidth, CCScreenHeight));
    this->addChild(layerColor,-100);

    
    CCMenuItemImage* item = CCMenuItemImage::create();
    item->setContentSize(CCSizeMake(CCScreenWidth, CCScreenHeight));
    CCMenu* menu = CCMenu::create(item, NULL);
    menu->setTouchPriority(-999);
    this->addChild(menu,-100);
    
	return true;
}

ItemBuyLayer *ItemBuyLayer::create(ItemPropertyStruct itemIt)
{
    
    ItemBuyLayer *node = new ItemBuyLayer;
	node->initWithInfo(itemIt);
	node->autorelease();
	return node;
}

bool ItemBuyLayer::initWithFile()
{
    CCSprite *bodySprite = UITools::createSprite(m_itemIt.type==1?"window-weapon.png":"window-item.png");
    bodySprite->setPosition(ccp(CCScreenWidth/2, CCScreenHeight/1.9));
    this->addChild(bodySprite);
    
    CCLabelTTF *ttf = CCLabelTTF::create(m_itemIt.describe.c_str(),"AmericanTypewriter",20,CCSizeMake(bodySprite->getContentSize().width-250,bodySprite->getContentSize().height-250),kCCTextAlignmentLeft);
    ttf->setPosition(ccp(bodySprite->getContentSize().width/2,bodySprite->getContentSize().height/6));
    bodySprite->addChild(ttf,1);
    
    CCSprite *itemSprite = UITools::createSprite("frame.png");
    itemSprite->setPosition(ccp(CCScreenWidth/2, CCScreenHeight/1.3));
    this->addChild(itemSprite);
    
    CCSprite *itemImage = UITools::createSprite(m_itemIt.imageFile.c_str());
    itemImage->setScale(1.5);
    itemImage->setPosition(ccp(itemSprite->getContentSize().width/2, itemSprite->getContentSize().height/2.1));
    itemSprite->addChild(itemImage);
    
    closeBut = UITouchSprite::create("window-close.png","window-close.png");
    closeBut->setPosition(ccp(CCScreenWidth/1.45, CCScreenHeight/1.25));
    closeBut->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ItemBuyLayer::closeWindow)));
    closeBut->m_nPriority = -1000;
    closeBut->setTouchEnabled(true);
    this->addChild(closeBut);
    
    buyBut = UITouchSprite::create("button-buy.png","button-buy.png");
    buyBut->setPosition(ccp(CCScreenWidth/2, CCScreenHeight/9));
    buyBut->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ItemBuyLayer::buyAction)));
    buyBut->m_nPriority = -1000;
    buyBut->setTouchEnabled(false);
    this->addChild(buyBut);
    
    CCSprite *icoSprite = UITools::createSprite("coin-stash.png");
    icoSprite->setPosition(ccp(buyBut->getContentSize().width/1.6, buyBut->getContentSize().height/2));
    CCLabelTTF *moneyLabel = CCLabelTTF::create(m_itemIt.price.c_str(), "AmericanTypewriter-Bold", 25);
    moneyLabel->setPosition(ccp(buyBut->getContentSize().width/2.5, buyBut->getContentSize().height/2));
    buyBut->addChild(moneyLabel);
    buyBut->addChild(icoSprite);
    buyBut->setVisible(false);
    
    equipBut = UITouchSprite::create("button-equip.png","button-equip.png");
    equipBut->setPosition(ccp(CCScreenWidth/2, CCScreenHeight/9));
    equipBut->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ItemBuyLayer::equipAction)));
    equipBut->m_nPriority = -1000;
    equipBut->setTouchEnabled(false);
    this->addChild(equipBut);
    equipBut->setVisible(false);
    if (m_itemIt.number==0) {
        buyBut->setVisible(true);
        buyBut->setTouchEnabled(true);
        
        itemSpriteIcon = UITools::createSprite(m_itemIt.imageFile.c_str());
        itemSpriteIcon->setScale(0.8);
        itemSpriteIcon->setPosition(ccp(CCScreenWidth*0.05, CCScreenHeight/1.25));
        this->addChild(itemSpriteIcon);
        
        m_numberLabel = CCLabelTTF::create(CCString::createWithFormat("%d",number)->getCString(), "AmericanTypewriter-Bold", 30);
        m_numberLabel->setPosition(ccp(CCScreenWidth*0.1, CCScreenHeight/1.25));
        this->addChild(m_numberLabel);
        
        CCSprite *itemIcon = UITools::createSprite("coin-stash.png");
        itemIcon->setPosition(ccp(CCScreenWidth*0.05, CCScreenHeight/1.1));
        this->addChild(itemIcon);
        
        m_moneyLabel = CCLabelTTF::create("100", "AmericanTypewriter-Bold", 30);
        m_moneyLabel->setPosition(ccp(CCScreenWidth*0.1, CCScreenHeight/1.1));
        this->addChild(m_moneyLabel);
    }else{
        equipBut->setVisible(true);
        equipBut->setTouchEnabled(true);
    }
    
	return init();
}

bool ItemBuyLayer::initWithInfo(ItemPropertyStruct itemIt)
{
    m_itemIt = itemIt;
    this->initWithFile();
    return true;
}

void ItemBuyLayer::closeWindow(CCNode *node)
{
    if (buyBut) {
        buyBut->setTouchEnabled(false);
    }
    if (equipBut) {
        equipBut->setTouchEnabled(false);
    }
    closeBut->setTouchEnabled(false);
    
    this->removeFromParent();
}

void ItemBuyLayer::buyAction(CCNode *node)
{
    if( m_ClickCallback)
        m_ClickCallback->execute();
    //this->removeFromParent();
}

void ItemBuyLayer::equipAction(CCNode *node)
{
    if( m_ClickCallback)
        m_ClickCallback->execute();
    //this->removeFromParent();
}

void ItemBuyLayer::setClickCallback( CCCallFuncN *callback )
{
	if(m_ClickCallback != callback)
	{
		CC_SAFE_RELEASE( m_ClickCallback);
		callback->retain();
		m_ClickCallback = callback;
		m_ClickCallback->setTarget(this);
	}
}

void ItemBuyLayer::runSpiderWiggleSequence(CCSprite *spider)
{
    CCScaleTo* scaleUp = CCScaleTo::create(0.1f, 1.0f);
    //CCEaseBackInOut *easeUp = CCEaseBackInOut::create(scaleUp);
    CCScaleTo *scaleDown = CCScaleTo::create(0.1f, 0.8f);
    //CCEaseBackInOut *easeDown = CCEaseBackInOut::create(scaleDown);
    CCSequence *scaleSequence = CCSequence::create(scaleUp,scaleDown,NULL);
    spider->runAction(scaleSequence);
}

void ItemBuyLayer::onEnter()
{
    CCLayer::onEnter();
}

void ItemBuyLayer::onExit()
{
    CCLayer::onExit();
    closeBut->setTouchEnabled(false);
    buyBut->setTouchEnabled(false);
    equipBut->setTouchEnabled(false);
}
//
//  ItemsForShopwindowNode.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-18.
//
//

#include "ItemsForStashNode.h"
#include "UITools.h"
#include "SimpleAudioEngine.h"
ItemsForStashNode::ItemsForStashNode(void)
:m_bgSprite(NULL),
m_ClickCallback(NULL)
{
	this->ignoreAnchorPointForPosition(false);
}


ItemsForStashNode::~ItemsForStashNode(void)
{
}

ItemsForStashNode* ItemsForStashNode::create( CCDictionary *infoDic)
{
    ItemsForStashNode *node = new ItemsForStashNode;
	node->initWithInfo(infoDic);
	node->autorelease();
    
    UITouchSprite *sprite = UITouchSprite::create(node->itemInfo.imageFile.c_str(),node->itemInfo.imageFile.c_str());
    UITouchSprite *priceSprite = UITouchSprite::create("button-item-number.png","button-item-number.png");
    CCLabelTTF *moneyLabel = CCLabelTTF::create(CCString::createWithFormat("%d",node->itemInfo.number)->getCString(), "AmericanTypewriter-Bold", 20);
    moneyLabel->setPosition(ccp(priceSprite->getContentSize().width/2, priceSprite->getContentSize().height/2));
    
    priceSprite->addChild(moneyLabel);
    
	return node->create(sprite,priceSprite);
}

ItemsForStashNode* ItemsForStashNode::create( const char *bgImg,int money )
{
    UITouchSprite *sprite = UITouchSprite::create(bgImg,bgImg);
    
    UITouchSprite *priceSprite = UITouchSprite::create("button-item-number.png","button-item-number.png");
    
    CCLabelTTF *moneyLabel = CCLabelTTF::create("3", "AmericanTypewriter-Bold", 20);
    moneyLabel->setPosition(ccp(priceSprite->getContentSize().width/2, priceSprite->getContentSize().height/2));
    priceSprite->addChild(moneyLabel);
	//CCSprite *sprite = UITools::createSprite(bgImg);
    //CCSprite *sprite = CCSprite::create(bgImg);
	return ItemsForStashNode::create(sprite,priceSprite);
}

ItemsForStashNode* ItemsForStashNode::create( UITouchSprite *bgSprite,UITouchSprite *priceSprite )
{
	ItemsForStashNode *node = new ItemsForStashNode;
	node->initWithSprite(bgSprite,priceSprite);
	node->autorelease();
	return node;
}

ItemsForStashNode* ItemsForStashNode::create( CCSize &size )
{
	ItemsForStashNode *node = new ItemsForStashNode;
	node->initWithSize(size);
	node->autorelease();
	return node;
}

void ItemsForStashNode::setBackground( UITouchSprite *bgSprite,UITouchSprite *priceSprite )
{
	bgSprite->setPosition(ccp(30,bgSprite->getContentSize().height *.5));
    bgSprite->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ItemsForStashNode::showInfoAction)));
    bgSprite->setTouchEnabled(true);
	this->addChild(bgSprite);
	m_bgSprite = bgSprite;
    
    priceSprite->setPosition(ccp(priceSprite->getContentSize().width * .5,-10));
    priceSprite->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ItemsForStashNode::showInfoAction)));
    priceSprite->setTouchEnabled(true);
    this->addChild(priceSprite);
	m_priceSprite = priceSprite;
}

void ItemsForStashNode::setClickCallback( CCCallFuncN *callback )
{
	if(m_ClickCallback != callback)
	{
		CC_SAFE_RELEASE( m_ClickCallback);
		callback->retain();
		m_ClickCallback = callback;
		m_ClickCallback->setTarget(this);
	}
}

void ItemsForStashNode::showInfoAction(CCNode *node)
{
    if( m_ClickCallback)
        m_ClickCallback->execute();
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("WeaponShop.wav");
}

bool ItemsForStashNode::init()
{
	return true;
}

bool ItemsForStashNode::initWithFile( const char *bgImg )
{
    UITouchSprite *sprite = UITouchSprite::create(bgImg);
	//CCSprite *sprite = UITools::createSprite(bgImg);
    //CCSprite *sprite = CCSprite::create(bgImg);
	CCSize size = sprite->getContentSize();
	//setBackground(sprite);
	return initWithSize(size);
}

bool ItemsForStashNode::initWithSprite( UITouchSprite *sprite,UITouchSprite *priceSprite )
{
    
	CCSize size1 = sprite->getContentSize();
    CCSize size2 = priceSprite->getContentSize();
    CCSize size;
    if (size1.width > size2.width) {
        size.width = size1.width;
    }else if(size1.width < size2.width){
        size.width = size2.width;
    }else{
        size.width = size2.width;
    }
    
    size.height = size1.height+size2.height;
	setBackground(sprite,priceSprite);
	return initWithSize(size);
}

bool ItemsForStashNode::initWithSize( CCSize &size )
{
	this->setAnchorPoint(ccp(.5,.5));
	this->setContentSize(size);
    
	return init();
}

bool ItemsForStashNode::initWithInfo(CCDictionary *infoDic)
{
    CCString *idstr = (CCString*)infoDic->objectForKey("id");
    itemInfo.id = idstr->intValue();
    
    CCString *imagestr = (CCString*)infoDic->objectForKey("image");
    itemInfo.imageFile = imagestr->getCString();
    
    CCString *pricestr = (CCString*)infoDic->objectForKey("price");
    itemInfo.price = pricestr->getCString();
    
    CCString *desstr = (CCString*)infoDic->objectForKey("describe");
    itemInfo.describe = desstr->getCString();
    
    CCString *numstr = (CCString*)infoDic->objectForKey("number");
    itemInfo.number = numstr->intValue();
    
    CCString *typestr = (CCString*)infoDic->objectForKey("type");
    itemInfo.type = typestr->intValue();
    
    return true;
}

void ItemsForStashNode::onEnter()
{
    CCNode::onEnter();
}

void ItemsForStashNode::onExit()
{
    CCNode::onExit();
    m_bgSprite->setTouchEnabled(false);
    m_priceSprite->setTouchEnabled(false);
}
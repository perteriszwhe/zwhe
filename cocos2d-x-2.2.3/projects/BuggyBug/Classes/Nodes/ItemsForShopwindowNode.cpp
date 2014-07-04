//
//  ItemsForShopwindowNode.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-18.
//
//

#include "ItemsForShopwindowNode.h"
#include "UITools.h"
#include "SimpleAudioEngine.h"
ItemsForShopwindowNode::ItemsForShopwindowNode(void)
:m_bgSprite(NULL),
m_ClickCallback(NULL)
{
	this->ignoreAnchorPointForPosition(false);
}


ItemsForShopwindowNode::~ItemsForShopwindowNode(void)
{
}

ItemsForShopwindowNode* ItemsForShopwindowNode::create( CCDictionary *infoDic)
{
    ItemsForShopwindowNode *node = new ItemsForShopwindowNode;
	node->initWithInfo(infoDic);
	node->autorelease();
    
    UITouchSprite *sprite = UITouchSprite::create(node->itemInfo.imageFile.c_str(),node->itemInfo.imageFile.c_str());
    
    UITouchSprite *priceSprite = UITouchSprite::create("button-price.png","button-price.png");
    
    CCSprite *icoSprite = UITools::createSprite("coin-price.png");
    icoSprite->setPosition(ccp(priceSprite->getContentSize().width/1.5, priceSprite->getContentSize().height/2));
    
    CCLabelTTF *moneyLabel = CCLabelTTF::create(node->itemInfo.price.c_str(), "AmericanTypewriter-Bold", 16);
    moneyLabel->setPosition(ccp(priceSprite->getContentSize().width/2.6, priceSprite->getContentSize().height/2));
    
    priceSprite->addChild(moneyLabel);
    priceSprite->addChild(icoSprite);
    
	return node->create(sprite,priceSprite);
}


ItemsForShopwindowNode* ItemsForShopwindowNode::create( const char *bgImg,int money)
{
    UITouchSprite *sprite = UITouchSprite::create(bgImg,bgImg);
    
    UITouchSprite *priceSprite = UITouchSprite::create("button-price.png");
    CCSprite *icoSprite = UITools::createSprite("coin-price.png");
    icoSprite->setPosition(ccp(priceSprite->getContentSize().width/1.5, priceSprite->getContentSize().height/2));
    CCLabelTTF *moneyLabel = CCLabelTTF::create("25", "AmericanTypewriter-Bold", 16);
    moneyLabel->setPosition(ccp(priceSprite->getContentSize().width/2.6, priceSprite->getContentSize().height/2));
    priceSprite->addChild(moneyLabel);
    priceSprite->addChild(icoSprite);
	//CCSprite *sprite = UITools::createSprite(bgImg);
    //CCSprite *sprite = CCSprite::create(bgImg);
	return ItemsForShopwindowNode::create(sprite,priceSprite);
}

ItemsForShopwindowNode* ItemsForShopwindowNode::create( UITouchSprite *bgSprite,UITouchSprite *priceSprite)
{
	ItemsForShopwindowNode *node = new ItemsForShopwindowNode;
	node->initWithSprite(bgSprite,priceSprite);
	node->autorelease();
	return node;
}

ItemsForShopwindowNode* ItemsForShopwindowNode::create( CCSize &size )
{
	ItemsForShopwindowNode *node = new ItemsForShopwindowNode;
	node->initWithSize(size);
	node->autorelease();
	return node;
}

void ItemsForShopwindowNode::setBackground( UITouchSprite *bgSprite,UITouchSprite *priceSprite  )
{
	bgSprite->setPosition(ccp(35,bgSprite->getContentSize().height *.5));
    bgSprite->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ItemsForShopwindowNode::showInfoAction)));
    bgSprite->setTouchEnabled(true);
    bgSprite->m_nPriority = 0;
	this->addChild(bgSprite);
	m_bgSprite = bgSprite;
    
    priceSprite->setPosition(ccp(priceSprite->getContentSize().width * .5,-10));
    priceSprite->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ItemsForShopwindowNode::showInfoAction)));
    priceSprite->setTouchEnabled(true);
    this->addChild(priceSprite);
	m_priceSprite = priceSprite;
}

void ItemsForShopwindowNode::setClickCallback( CCCallFuncN *callback )
{
	if(m_ClickCallback != callback)
	{
		CC_SAFE_RELEASE( m_ClickCallback);
		callback->retain();
		m_ClickCallback = callback;
		m_ClickCallback->setTarget(this);
	}
}

void ItemsForShopwindowNode::showInfoAction(CCNode *node)
{
//    m_itemBuyLayer = ItemBuyLayer::create(item);
//    m_itemBuyLayer->setVisible(true);
//    m_storeScene->addChild(m_itemBuyLayer);
//    m_itemBuyLayer->show();
    if( m_ClickCallback)
        m_ClickCallback->execute();
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("WeaponShop.wav");
    
}

bool ItemsForShopwindowNode::init()
{
	return true;
}

bool ItemsForShopwindowNode::initWithFile( const char *bgImg )
{
    UITouchSprite *sprite = UITouchSprite::create(bgImg);
	//CCSprite *sprite = UITools::createSprite(bgImg);
    //CCSprite *sprite = CCSprite::create(bgImg);
	CCSize size = sprite->getContentSize();
	//setBackground(sprite);
	return initWithSize(size);
}

bool ItemsForShopwindowNode::initWithSprite( UITouchSprite *sprite,UITouchSprite *priceSprite )
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

bool ItemsForShopwindowNode::initWithSize( CCSize &size )
{
	this->setAnchorPoint(ccp(.5,.5));
	this->setContentSize(size);
    
	return init();
}

bool ItemsForShopwindowNode::initWithInfo(CCDictionary *infoDic)
{
    CCString *idstr = (CCString*)infoDic->objectForKey("id");
    itemInfo.id = idstr->intValue();
    
    CCString *imagestr = (CCString*)infoDic->objectForKey("image");
    itemInfo.imageFile = imagestr->getCString();
    
    CCString *pricestr = (CCString*)infoDic->objectForKey("price");
    itemInfo.price = pricestr->getCString();
    
    CCString *desstr = (CCString*)infoDic->objectForKey("describe");
    itemInfo.describe = desstr->getCString();
    
    CCString *typestr = (CCString*)infoDic->objectForKey("type");
    itemInfo.type = typestr->intValue();
    
    return true;
}

void ItemsForShopwindowNode::onEnter()
{
    CCNode::onEnter();
}

void ItemsForShopwindowNode::onExit()
{
    CCNode::onExit();
    m_bgSprite->setTouchEnabled(false);
    m_priceSprite->setTouchEnabled(false);
}
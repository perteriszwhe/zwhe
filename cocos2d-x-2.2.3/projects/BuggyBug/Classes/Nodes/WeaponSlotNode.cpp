//
//  WeaponSlotNode.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-16.
//
//

#include "WeaponSlotNode.h"
#include "UITools.h"
#include "AllDefines.h"
#include "StoreScene.h"
#include "DBUtil.h"

WeaponSlotNode::WeaponSlotNode(void)
:m_bgSprite(NULL)
{
	this->ignoreAnchorPointForPosition(false);
}


WeaponSlotNode::~WeaponSlotNode(void)
{
}

WeaponSlotNode* WeaponSlotNode::create( SlotType slotType,SlotFlag slotFlag )
{
    const char *bgImg;
	if (slotType == lock) {
        bgImg = "slot-locked.png";
    }else if(slotType == unlock){
        bgImg = "slot-unclocked.png";
    }
    WeaponSlotNode *node = WeaponSlotNode::create(bgImg);
    node->setSlotType(slotType);
    node->setSlotFlag(slotFlag);
    return node;
}

void WeaponSlotNode::setSlotType(SlotType slotType)
{
    m_slotType = slotType;
}

void WeaponSlotNode::setSlotFlag(SlotFlag slotFlag)
{
    m_slotFlag = slotFlag;
    switch (slotFlag) {
        case slotOne:
            this->setPosition(ccp(CCScreenWidth-330, CCScreenHeight-80));
            break;
        case slotTwo:
            this->setPosition(ccp(CCScreenWidth-270, CCScreenHeight-220));
            break;
        case slotThree:
            this->setPosition(ccp(CCScreenWidth-410, CCScreenHeight-190));
            break;
        case slotFour:
            this->setPosition(ccp(CCScreenWidth-520, CCScreenHeight-100));
            break;
        case slotFive:
            this->setPosition(ccp(CCScreenWidth-540, CCScreenHeight-250));
            break;
        default:
            break;
    }
}

WeaponSlotNode* WeaponSlotNode::create( const char *bgImg )
{
    UITouchSprite *sprite = UITouchSprite::create(bgImg,bgImg);
	//CCSprite *sprite = UITools::createSprite(bgImg);
    //CCSprite *sprite = CCSprite::create(bgImg);
	return WeaponSlotNode::create(sprite);
}

WeaponSlotNode* WeaponSlotNode::create( UITouchSprite *bgSprite )
{
	WeaponSlotNode *node = new WeaponSlotNode;
	node->initWithSprite(bgSprite);
	node->autorelease();
	return node;
}

WeaponSlotNode* WeaponSlotNode::create( CCSize &size )
{
	WeaponSlotNode *node = new WeaponSlotNode;
	node->initWithSize(size);
	node->autorelease();
	return node;
}

void WeaponSlotNode::setBackground( UITouchSprite *bgSprite )
{
	bgSprite->setPosition(ccp(bgSprite->getContentSize().width * .5,bgSprite->getContentSize().height *.5));
    bgSprite->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(WeaponSlotNode::unlockAction)));
    bgSprite->setTouchEnabled(true);
	this->addChild(bgSprite);
	m_bgSprite = bgSprite;
    
    numLabel = CCLabelTTF::create("0", "AmericanTypewriter-Bold", 25);
    numLabel->setPosition(ccp(bgSprite->getContentSize().width * .52,bgSprite->getContentSize().height *.18));
    m_bgSprite->addChild(numLabel);
    
    
}

bool WeaponSlotNode::init()
{
	return true;
}

bool WeaponSlotNode::initWithFile( const char *bgImg )
{
    UITouchSprite *sprite = UITouchSprite::create(bgImg);
	//CCSprite *sprite = UITools::createSprite(bgImg);
    //CCSprite *sprite = CCSprite::create(bgImg);
	CCSize size = sprite->getContentSize();
	setBackground(sprite);
	return initWithSize(size);
}

bool WeaponSlotNode::initWithSprite( UITouchSprite *sprite )
{
	CCSize size = sprite->getContentSize();
	setBackground(sprite);
	return initWithSize(size);
}

bool WeaponSlotNode::initWithSize( CCSize &size )
{
    itemSprite = NULL;
	this->setAnchorPoint(ccp(.5,.5));
	this->setContentSize(size);
    
	return init();
}

void WeaponSlotNode::unlockAction(CCNode *node)
{
    this->runSpiderWiggleSequence(m_bgSprite);
    if(m_slotType == lock)
    {
        this->setSlotType(unlock);
        CCSpriteFrame *frame = UITools::createSpriteFrame("slot-unclocked.png");
        m_bgSprite->setNormalSpriteFrame(frame);
        m_bgSprite->setSelectSpriteFrame(frame);
        
        CCTexture2D * text2d = CCTextureCache::sharedTextureCache()->
        addImage("slot-unclocked.png");
        m_bgSprite->setTexture(text2d);
        
        DBUtil::initDB("MyGameInfo.db");
        std::string insertTableSql = "insert into my_itemslot( slotid ) values ( "+CCString::createWithFormat("%d",m_slotFlag)->m_sString+");";
        DBUtil::insertData(insertTableSql);
        DBUtil::closeDB();
    }else{
        CCLog("点击了！！！");
        if (itemSprite) {
            DBUtil::initDB("MyGameInfo.db");
            std::string updateNumberSql = "delete from my_item where itemid = "+CCString::createWithFormat("%d",m_itemInfo.id)->m_sString+" and type = "+CCString::createWithFormat("%d",m_itemInfo.type)->m_sString+";";
            DBUtil::deleteData(updateNumberSql);
            DBUtil::closeDB();
            
            itemSprite->removeFromParent();
            numLabel->setString(CCString::createWithFormat("%d",0)->getCString());
            
            StoreScene *sc = (StoreScene*)m_storeScene;
            sc->stNode->addItem(m_itemInfo);
            
            //CC_SAFE_DELETE(m_itemInfo);
            m_itemInfo.id = NULL;
            m_itemInfo.number = NULL;
            m_itemInfo.imageFile = "";
            itemSprite = NULL;
        }
        
    }
}

void WeaponSlotNode::runSpiderWiggleSequence(UITouchSprite *spider)
{
    CCScaleTo* scaleUp = CCScaleTo::create(0.2f, 1.2f);
    //CCEaseBackInOut *easeUp = CCEaseBackInOut::create(scaleUp);
    CCScaleTo *scaleDown = CCScaleTo::create(0.2f, 1.0f);
    //CCEaseBackInOut *easeDown = CCEaseBackInOut::create(scaleDown);
    CCSequence *scaleSequence = CCSequence::create(scaleUp,scaleDown,NULL);
    spider->runAction(scaleSequence);
}

void WeaponSlotNode::equipItem(ItemPropertyStruct itemInfo)
{
    if (itemInfo.id) {
        m_itemInfo = itemInfo;
    }
    itemSprite = UITools::createSprite(m_itemInfo.imageFile.c_str());
    itemSprite->setScale(0.8);
    itemSprite->setPosition(ccp(m_bgSprite->getContentSize().width * .53,m_bgSprite->getContentSize().height *.6));
    m_bgSprite->addChild(itemSprite);
    
    numLabel->setString(CCString::createWithFormat("%d",m_itemInfo.number)->getCString());
}

void WeaponSlotNode::onEnter()
{
    CCNode::onEnter();
}

void WeaponSlotNode::onExit()
{
    CCNode::onExit();
    m_bgSprite->setTouchEnabled(false);
}

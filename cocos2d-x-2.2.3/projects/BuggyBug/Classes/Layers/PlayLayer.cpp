//
//  PlayLayer.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-27.
//
//

#include "PlayLayer.h"
#include "UITools.h"
#include "AllDefines.h"
#include "GamePlayScene.h"
#include "ItemSlot.h"
#include "WeaponSlot.h"
#include "DBUtil.h"

static GamePlayScene* pNode;
PlayLayer::PlayLayer(void)
{
	this->ignoreAnchorPointForPosition(false);
}


PlayLayer::~PlayLayer(void)
{
}

PlayLayer* PlayLayer::create( CCArray *weaponArr,CCArray *itemArr )
{
    PlayLayer *node = new PlayLayer;
	node->initTitle();
    node->initItem();
	node->autorelease();
	return node;
}

bool PlayLayer::initTitle()
{
    pauseBut = UITouchSprite::create("HUD_109.png", "HUD_109.png");
    pauseBut->setPosition(ccp(50, CCScreenHeight/1.08));
    pauseBut->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(PlayLayer::pauseGameAction)));
    pauseBut->m_nPriority = -99;
    pauseBut->setTouchEnabled(true);
    this->addChild(pauseBut);
    
    m_TitleBgSprite = UITools::createSprite("HUD_116.png");
    m_TitleBgSprite->setPosition(ccp(CCScreenWidth/1.13, CCScreenHeight/1.15));
    this->addChild(m_TitleBgSprite);
    
    m_ScoresIcon = UITools::createSprite("HUD_98.png");
    m_ScoresIcon->setPosition(ccp(30,m_TitleBgSprite->getContentSize().height/1.3));
    m_TitleBgSprite->addChild(m_ScoresIcon);
    
    m_ScoresLabel = CCLabelTTF::create("0", "TrebuchetMS-Italic", 24);
    m_ScoresLabel->setPosition(ccp(80,m_TitleBgSprite->getContentSize().height/1.3));
    m_TitleBgSprite->addChild(m_ScoresLabel);
    
    m_CoinIcon = UITools::createSprite("HUD_100.png");
    m_CoinIcon->setPosition(ccp(130,m_TitleBgSprite->getContentSize().height/1.3));
    m_TitleBgSprite->addChild(m_CoinIcon);
    
    m_CoinLabel = CCLabelTTF::create("0", "TrebuchetMS-Italic", 24);
    m_CoinLabel->setPosition(ccp(180,m_TitleBgSprite->getContentSize().height/1.3));
    m_TitleBgSprite->addChild(m_CoinLabel);
    
    m_HPIcon = UITools::createSprite("HUD_106.png");
    m_HPIcon->setPosition(ccp(165,m_TitleBgSprite->getContentSize().height/2));
    m_TitleBgSprite->addChild(m_HPIcon);
    
    m_HPLabel = CCLabelTTF::create("10", "TrebuchetMS-Italic", 22);
    m_HPLabel->setPosition(ccp(195,m_TitleBgSprite->getContentSize().height/2));
    m_TitleBgSprite->addChild(m_HPLabel);
    
    m_TimeIcon = UITools::createSprite("HUD_103.png");
    m_TimeIcon->setPosition(ccp(165,m_TitleBgSprite->getContentSize().height/3.8));
    m_TitleBgSprite->addChild(m_TimeIcon);
    
    m_TimeLabel = CCLabelTTF::create("1", "TrebuchetMS-Italic", 22);
    m_TimeLabel->setPosition(ccp(195,m_TitleBgSprite->getContentSize().height/3.8));
    m_TitleBgSprite->addChild(m_TimeLabel);
    
    return true;
}

bool PlayLayer::initItem()
{
    DBUtil::initDB("MyGameInfo.db");
    std::string selectAllSql = "select * from my_item where type=2 and equipSlotIndex>0;";
    CCArray *dataArray = DBUtil::getAllDataInfo(selectAllSql);
    DBUtil::closeDB();
    UILoaderItem *itemLoader = (UILoaderItem*)ConfigCache::sharedConfigCache()->getConfig(xml_type_item);
    
    for (int i=0; i<dataArray->count(); i++) {
        CCDictionary *dic = (CCDictionary*)dataArray->objectAtIndex(i);
        CCString *idstr = (CCString*)dic->objectForKey("id");
        CCString *typestr = (CCString*)dic->objectForKey("type");
        CCString *numberstr = (CCString*)dic->objectForKey("number");
        //CCString *equipslotindexstr = (CCString*)dic->objectForKey("equipSlotIndex");
        
        ItemPropertyStruct itemIt = itemLoader->getProperty(typestr->intValue(),idstr->intValue());
        itemIt.number = numberstr->intValue();
        
        ItemSlot *itemSlot = ItemSlot::createWithType((SlotIndex)(i+1));
        itemSlot->setPosition(ccp(CCScreenWidth*0.05, CCScreenHeight*0.01));
        this->addChild(itemSlot);
        itemSlot->equipItem(itemIt);
    }
    
    return initWeapon();
}

bool PlayLayer::initWeapon()
{
    DBUtil::initDB("MyGameInfo.db");
    std::string selectAllSql = "select * from my_item where type=1 and equipSlotIndex>0;";
    CCArray *dataArray = DBUtil::getAllDataInfo(selectAllSql);
    DBUtil::closeDB();
    
    if (dataArray->count()>0) {
        WeaponSlot *weaponSlot = WeaponSlot::create("HUD_03.png");
        weaponSlot->m_storeScene = this;
        weaponSlot->setPosition(ccp(CCScreenWidth*0.93, CCScreenHeight*0.15));
        this->addChild(weaponSlot);
        weaponSlot->loadEquipWeapon(dataArray);
    }
    return init();
}

bool PlayLayer::init()
{
    this->setTouchEnabled(true);
    return true;
}

void PlayLayer::pauseGameAction(CCNode *node)
{
    pNode->m_pause->show();
    CCDirector::sharedDirector()->pause();
}

void PlayLayer::onEnterTransitionDidFinish()
{
    pNode = (GamePlayScene*)getParent();
}

void PlayLayer::onEnter()
{
    CCLayer::onEnter();
//    CCDirector* pDirector = CCDirector::sharedDirector();
//    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void PlayLayer::onExit()
{
    CCLayer::onExit();
//    CCDirector* pDirector = CCDirector::sharedDirector();
//    pDirector->getTouchDispatcher()->removeDelegate(this);
}

bool PlayLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void PlayLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}
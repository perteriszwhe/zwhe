//
//  StoreScene.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-15.
//
//

#include "StoreScene.h"
#include "AllDefines.h"
#include "WeaponSlotNode.h"
#include "UITouchSprite.h"
#include "GameMianScene.h"
#include "ItemBuyLayer.h"
#include "SimpleAudioEngine.h"
#include "DBUtil.h"


CCScene* StoreScene::scene()
{
    CCScene *scene = CCScene::create();
    StoreScene *layer = StoreScene::create();
    scene->addChild(layer);
    return scene;
}

StoreScene::StoreScene(void)
{
    
}


StoreScene::~StoreScene(void)
{
    
}

bool StoreScene::init()
{
    if( !CCLayer::init()) return false;
    this->initDB();
    this->setBackgroundWall();
    this->setWeaponSlot();
    this->setItemSlot();
    this->setShopwindow();
    this->setStashNode();
    return true;
}

void StoreScene::initDB()
{
    DBUtil::initDB("MyGameInfo.db");
    std::string createTableSql = "create table my_item (id integer primary key autoincrement,itemid integer,type integer,number integer,equipSlotIndex integer);";
    DBUtil::createTable(createTableSql, "my_item");
    DBUtil::closeDB();
    
    DBUtil::initDB("MyGameInfo.db");
    std::string createTableSql2 = "create table my_itemslot (id integer primary key autoincrement,slotid integer);";
    DBUtil::createTable(createTableSql2, "my_itemslot");
    DBUtil::closeDB();
}

void StoreScene::setBackgroundWall()
{
    CCLayer *wallLayer = CCLayer::create();
    wallLayer->setContentSize(CCSize(100, 100));
    
    m_bgSprite = CCSprite::create("store_background.png");
    m_bgSprite->setPosition(ccp(CCScreenWidth/2, CCScreenHeight/2));
    wallLayer->addChild(m_bgSprite,-1);
    
    eyes = CCSprite::create("bk-eyes.png");
    eyes->setPosition(ccp(CCScreenWidth-70, 160));
    wallLayer->addChild(eyes);
    schedule(schedule_selector(StoreScene::eyesBlinkAction),3.0f);
    
    this->addChild(wallLayer,-1);
    
//    m_itemBuyLayer = ItemBuyLayer::create(item);
//    m_itemBuyLayer->setVisible(true);
//    this->addChild(m_itemBuyLayer , 200);
//    m_itemBuyLayer->show();
}

void StoreScene::eyesBlinkAction()
{
    eyes->runAction(CCBlink::create(0.5, 2));
}

void StoreScene::setWeaponSlot()
{
    DBUtil::initDB("MyGameInfo.db");
    std::string selectAllSql = "select * from my_item where type=2 and equipSlotIndex>0;";
    CCArray *dataArray = DBUtil::getAllDataInfo(selectAllSql);
    DBUtil::closeDB();
    UILoaderItem *itemLoader = (UILoaderItem*)ConfigCache::sharedConfigCache()->getConfig(xml_type_item);
    
    for (int i=1; i<6; i++) {
        
        DBUtil::initDB("MyGameInfo.db");
        std::string selectAllSql = "select * from my_itemslot where slotid="+CCString::createWithFormat("%d",i)->m_sString+";";
        int res = DBUtil::getDataInfo(selectAllSql);
        DBUtil::closeDB();
        
        WeaponSlotNode *wNode;
        if (res>0) {
            wNode = WeaponSlotNode::create(unlock, (SlotFlag)i);
        }else{
            wNode = WeaponSlotNode::create(lock, (SlotFlag)i);
        }
        for (int a=0; a<dataArray->count(); a++) {
            CCDictionary *dic = (CCDictionary*)dataArray->objectAtIndex(a);
            CCString *idstr = (CCString*)dic->objectForKey("id");
            CCString *typestr = (CCString*)dic->objectForKey("type");
            CCString *numberstr = (CCString*)dic->objectForKey("number");
            CCString *equipslotindexstr = (CCString*)dic->objectForKey("equipSlotIndex");
            
            ItemPropertyStruct itemIt = itemLoader->getProperty(typestr->intValue(),idstr->intValue());
            itemIt.number = numberstr->intValue();
            
            if (i == equipslotindexstr->intValue()) {
                wNode->equipItem(itemIt);
            }
        }
        
        wNode->setTag((SlotFlag)i);
        wNode->m_storeScene = this;
        this->addChild(wNode);
    }
    exitBut = UITouchSprite::create("button-exit.png", "button-exit.png");
    exitBut->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(StoreScene::exitAction)));
    exitBut->setPosition(ccp(CCScreenWidth/1.1, CCScreenHeight/12));
    exitBut->setTouchEnabled(true);
    this->addChild(exitBut);
}

void StoreScene::setItemSlot()
{
    iNode = ItemSlotNode::create("slot-weapon.png");
    iNode->m_storeScene = this;
    
    DBUtil::initDB("MyGameInfo.db");
    std::string selectAllSql = "select * from my_item where type=1 and equipSlotIndex>0;";
    CCArray *dataArray = DBUtil::getAllDataInfo(selectAllSql);
    DBUtil::closeDB();
    iNode->loadEquipWeapon(dataArray);
    
    iNode->setPosition(ccp(CCScreenWidth/1.1, CCScreenHeight/1.6));
    this->addChild(iNode);
}

void StoreScene::exitAction(CCNode *node)
{
    this->runSpiderWiggleSequence(exitBut);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCTransitionMoveInT* transition = CCTransitionMoveInT ::create(0.5f,GameMianScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}

void StoreScene::runSpiderWiggleSequence(UITouchSprite *spider)
{
    CCScaleTo* scaleUp = CCScaleTo::create(0.1f, 1.2f);
    CCScaleTo *scaleDown = CCScaleTo::create(0.1f, 1.0f);
    CCSequence *scaleSequence = CCSequence::create(scaleUp,scaleDown,NULL);
    spider->runAction(scaleSequence);
}

void StoreScene::setShopwindow()
{
    sNode = ShopwindowNode::create("store.png");
    sNode->m_storeScene = this;
    sNode->setPosition(ccp(CCScreenWidth/4, CCScreenHeight/2));
    this->addChild(sNode);
}

void StoreScene::setStashNode()
{
    stNode = StashNode::create("stash.png");
    stNode->m_storeScene = this;
    
    DBUtil::initDB("MyGameInfo.db");
    std::string selectAllSql = "select * from my_item where equipSlotIndex=0;";
    CCArray *dataArray = DBUtil::getAllDataInfo(selectAllSql);
    DBUtil::closeDB();
    stNode->loadMyData(dataArray);
    
    stNode->setPosition(ccp(CCScreenWidth/1.52, CCScreenHeight/3.55));
    this->addChild(stNode);
}

void StoreScene::buyAction(CCNode *node)
{
    StoreScene *sc = (StoreScene*)sNode->m_storeScene;
    CCLOG("%s",sc->stNode->numLabel->getString());
    ItemBuyLayer *buyLayer = (ItemBuyLayer*)node;
    if(!stNode->updateMoney(buyLayer->m_itemIt.price.c_str()))
    {
        CCMessageBox("您的金币不足！", "购买失败");
    }
}

void StoreScene::onEnter()
{
	CCLayer::onEnter();
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("storebg.mp3", true);
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Welcometotheshop.wav");
}

void StoreScene::onExit()
{
    CCLayer::onExit();
}
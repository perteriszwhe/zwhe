//
//  StashNode.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-16.
//
//

#include "StashNode.h"
#include "UITools.h"
#include "AllDefines.h"
#include "StashCell.h"
#include "ItemsForShopwindowNode.h"
#include "ItemsForStashNode.h"
#include "StoreScene.h"
#include "WeaponSlotNode.h"
#include "ItemSlotNode.h"
#include "SimpleAudioEngine.h"
#include "DBUtil.h"

StashNode::StashNode(void)
:m_bgSprite(NULL)
{
	this->ignoreAnchorPointForPosition(false);
}


StashNode::~StashNode(void)
{
    
}

bool StashNode::init()
{
    dataArr = CCArray::create();
    dataArr->retain();
    
    tableview = CCTableView::create(this, CCSizeMake(275, 220));
    tableview->setDirection(kCCScrollViewDirectionVertical); //设置tableview的方向是竖直方向，当然也有水平方向
    tableview->setDelegate(this);
    tableview->setVerticalFillOrder(kCCTableViewFillTopDown);// 设置tableview cell的index排列，这里设置是从上到下变大，当然也可以从下到上变大。
    tableview->setPosition(ccp(100,80));
    tableview->setTouchPriority(-1028);
    this->addChild(tableview);
    
	return true;
}

StashNode* StashNode::create( const char *bgImg )
{
    UITouchSprite *sprite = UITouchSprite::create(bgImg,bgImg);
	//CCSprite *sprite = UITools::createSprite(bgImg);
    //CCSprite *sprite = CCSprite::create(bgImg);
	return StashNode::create(sprite);
}

StashNode* StashNode::create( CCSprite *bgSprite )
{
	StashNode *node = new StashNode;
	node->initWithSprite(bgSprite);
	node->autorelease();
	return node;
}

StashNode* StashNode::create( CCSize &size )
{
	StashNode *node = new StashNode;
	node->initWithSize(size);
	node->autorelease();
	return node;
}

void StashNode::setBackground( CCSprite *bgSprite )
{
	bgSprite->setPosition(ccp(bgSprite->getContentSize().width * .5,bgSprite->getContentSize().height *.5));
	this->addChild(bgSprite);
	m_bgSprite = bgSprite;
    
    CCSprite *icoSprite = UITools::createSprite("coin-stash.png");
    icoSprite->setPosition(ccp(bgSprite->getContentSize().width* .6, bgSprite->getContentSize().height/1.22));
    this->addChild(icoSprite);
    
    numLabel = CCLabelTTF::create("252", "AmericanTypewriter-Bold", 30);
    numLabel->setPosition(ccp(bgSprite->getContentSize().width* .46, bgSprite->getContentSize().height/1.22));
    this->addChild(numLabel);
}

bool StashNode::initWithFile( const char *bgImg )
{
	CCSprite *sprite = UITools::createSprite(bgImg);
	CCSize size = sprite->getContentSize();
	setBackground(sprite);
	return initWithSize(size);
}

bool StashNode::initWithSprite( CCSprite *sprite )
{
	CCSize size = sprite->getContentSize();
	setBackground(sprite);
	return initWithSize(size);
}

bool StashNode::initWithSize( CCSize &size )
{
	this->setAnchorPoint(ccp(.5,.5));
	this->setContentSize(size);
    
	return init();
}



void StashNode::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
    CCLOG("you touch cell index = %u",cell->getIdx());
}

CCSize StashNode::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(275, 110);
}

unsigned int StashNode::numberOfCellsInTableView(CCTableView *table)
{
    int row;
    CCLOG("%d",dataArr->count()%3);
    if (dataArr->count()%3==0) {
        row = dataArr->count()/3;
    }else{
        row = dataArr->count()/3+1;
    }
    return row;
}

CCTableViewCell* StashNode::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
//    CCTableViewCell *cell = table->dequeueCell();
//    if (!cell) {
//        cell = new StashCell();
//        cell->autorelease();
//        
//        //添加背景图片
//        //        CCSprite *sprite = CCSprite::create("111.png");
//        //        sprite->setAnchorPoint(CCPointZero);
//        //        sprite->setPosition(ccp(0, 0));
//        //        cell->addChild(sprite,1);
//        
//        ItemsForStashNode *sprite1 = ItemsForStashNode::create("item1.png", 25);
//        sprite1->setAnchorPoint(CCPointZero);
//        sprite1->setPosition(ccp(20, 15));
//        sprite1->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(StashNode::showInfoAction)));
//        cell->addChild(sprite1,1);
//        
//        //添加背景图片
//        ItemsForStashNode *sprite2 = ItemsForStashNode::create("item2.png", 25);
//        sprite2->setAnchorPoint(CCPointZero);
//        sprite2->setPosition(ccp(110, 15));
//        sprite2->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(StashNode::showInfoAction)));
//        cell->addChild(sprite2,1);
//        
//        //添加背景图片
//        ItemsForStashNode *sprite3 = ItemsForStashNode::create("item3.png", 25);
//        sprite3->setAnchorPoint(CCPointZero);
//        sprite3->setPosition(ccp(200, 15));
//        sprite3->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(StashNode::showInfoAction)));
//        cell->addChild(sprite3,1);
//    }
//    else
//    {
//        
//    }
//    
//    return cell;
    
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new StashCell();
        cell->autorelease();
    }
    CCArray *arr = cell->getChildren();
    if (arr) {
        for (int i=0;i<arr->count();i++) {
            ItemsForStashNode *itemNode = (ItemsForStashNode*)arr->objectAtIndex(i);
            itemNode->m_bgSprite->setTouchEnabled(false);
            itemNode->m_priceSprite->setTouchEnabled(false);
        }
    }
    cell->removeAllChildrenWithCleanup(true);
    for (int i=idx*3; i<idx*3+3; i++) {
        if (i<dataArr->count()) {
            CCDictionary *dic = (CCDictionary*)dataArr->objectAtIndex(i);
            ItemsForStashNode *sprite1 = ItemsForStashNode::create(dic);
            
            CCString *idstr = (CCString*)dic->objectForKey("id");
            sprite1->itemInfo.id = idstr->intValue();
            
            CCString *imagestr = (CCString*)dic->objectForKey("image");
            sprite1->itemInfo.imageFile = imagestr->getCString();
            
            CCString *pricestr = (CCString*)dic->objectForKey("price");
            sprite1->itemInfo.price = pricestr->getCString();
            
            CCString *desstr = (CCString*)dic->objectForKey("describe");
            sprite1->itemInfo.describe = desstr->getCString();
            
            CCString *typestr = (CCString*)dic->objectForKey("type");
            sprite1->itemInfo.type = typestr->intValue();
            
            CCString *numberstr = (CCString*)dic->objectForKey("number");
            sprite1->itemInfo.number = numberstr->intValue();
            
            sprite1->setAnchorPoint(CCPointZero);
            switch (idx*3+3-i) {
                case 3:
                    sprite1->setPosition(ccp(20, 15));
                    break;
                case 2:
                    sprite1->setPosition(ccp(110, 15));
                    break;
                case 1:
                    sprite1->setPosition(ccp(200, 15));
                    break;
                default:
                    break;
            }
            sprite1->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(StashNode::showInfoAction)));
            cell->addChild(sprite1,1);
        }
    }
    return cell;
}

bool StashNode::isMoney(const char *money)
{
    int currMoney = std::atoi(numLabel->getString());
    int updateMoney = std::atoi(money);
    if (currMoney>=updateMoney) {
        return true;
    }else{
        return false;
    }
}

bool StashNode::updateMoney(const char *money)
{
    int currMoney = std::atoi(numLabel->getString());
    int updateMoney = std::atoi(money);
    if (currMoney>=updateMoney) {
        numLabel->setString(CCString::createWithFormat("%d",currMoney-updateMoney)->getCString());
        return true;
    }else{
        return false;
    }
}

bool StashNode::addItem(ItemPropertyStruct itemIt)
{
    bool isHave = false;
    bool isAdd = false;
    for (int i=0; i<dataArr->count(); i++) {
        CCDictionary *dic = (CCDictionary*)dataArr->objectAtIndex(i);
        CCString *idstr = (CCString*)dic->objectForKey("id");
        CCString *typestr = (CCString*)dic->objectForKey("type");
        if (idstr->intValue() == itemIt.id && typestr->intValue() == itemIt.type)
        {
            if (itemIt.type==1) {
                CCMessageBox("该武器已经购买过了！", "购买失败");
                isHave = true;
                isAdd = false;
            }else{
                isHave = true;
                CCString *numberstr = (CCString*)dic->objectForKey("number");
                dic->setObject(CCString::createWithFormat("%d",numberstr->intValue()+1), "number");
                tableview->reloadData();
                isAdd = true;
                
                
                DBUtil::initDB("MyGameInfo.db");
                std::string updateNumberSql = "update my_item set number = "+((CCString*)dic->objectForKey("number"))->m_sString+" where itemid = "+CCString::createWithFormat("%d",itemIt.id)->m_sString+" and type = "+CCString::createWithFormat("%d",itemIt.type)->m_sString+";";
                DBUtil::updateData(updateNumberSql);
                DBUtil::closeDB();
                
                return isAdd;
            }
        }
    }
    if (!isHave) {
        CCDictionary *dic = CCDictionary::create();
        dic->setObject(CCString::createWithFormat("%d",itemIt.id), "id");
        dic->setObject(CCString::createWithFormat("%s",itemIt.imageFile.c_str()), "image");
        dic->setObject(CCString::createWithFormat("%s",itemIt.price.c_str()), "price");
        dic->setObject(CCString::createWithFormat("%s",itemIt.describe.c_str()), "describe");
        dic->setObject(CCString::createWithFormat("%d",itemIt.number==0?1:itemIt.number), "number");
        dic->setObject(CCString::createWithFormat("%d",itemIt.type), "type");
        dataArr->addObject(dic);
        tableview->reloadData();
        isAdd = true;
        
        
        CCString* itemId=CCString::createWithFormat("%d",itemIt.id);
        CCString* itemType=CCString::createWithFormat("%d",itemIt.type);
        CCString* itemNumber=CCString::createWithFormat("%d",itemIt.number==0?1:itemIt.number);
        
        DBUtil::initDB("MyGameInfo.db");
        std::string insertTableSql = "insert into my_item( itemid,type,number,equipSlotIndex ) values ( "+itemId->m_sString+","+itemType->m_sString+","+itemNumber->m_sString+",0 );";
        //std::string insertTableSql = "insert into my_item( itemid,type,number ) values (3,2,10)";
        DBUtil::insertData(insertTableSql);
        DBUtil::closeDB();
    }
    return isAdd;
}

void StashNode::loadMyData(CCArray *itemArray)
{
//    CCDictionary *dic = CCDictionary::create();
//    dic->setObject(CCString::createWithFormat("%d",itemIt.id), "id");
//    dic->setObject(CCString::createWithFormat("%s",itemIt.imageFile.c_str()), "image");
//    dic->setObject(CCString::createWithFormat("%s",itemIt.price.c_str()), "price");
//    dic->setObject(CCString::createWithFormat("%s",itemIt.describe.c_str()), "describe");
//    dic->setObject(CCString::createWithFormat("%d",itemIt.number==0?1:itemIt.number), "number");
//    dic->setObject(CCString::createWithFormat("%d",itemIt.type), "type");
//    dataArr->addObject(dic);
//    tableview->reloadData();
    dataArr = itemArray;
    tableview->reloadData();
}

void StashNode::removeItem(ItemPropertyStruct itemIt)
{
    for (int i=0; i<dataArr->count(); i++) {
        CCDictionary *dic = (CCDictionary*)dataArr->objectAtIndex(i);
        CCString *idstr = (CCString*)dic->objectForKey("id");
        CCString *typestr = (CCString*)dic->objectForKey("type");
        if (idstr->intValue() == itemIt.id && typestr->intValue() == itemIt.type)
        {
            dataArr->removeObjectAtIndex(i);
            tableview->reloadData();
            return;
        }
    }
}

void StashNode::showInfoAction(CCNode *node)
{
    ItemsForStashNode *stashNode = (ItemsForStashNode*)node;
    m_itemBuyLayer = ItemBuyLayer::create(stashNode->itemInfo);
    m_itemBuyLayer->setVisible(true);
    m_itemBuyLayer->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(StashNode::equipAction)));
    m_storeScene->addChild(m_itemBuyLayer);
    m_itemBuyLayer->show();
}

void StashNode::equipAction(CCNode *node)
{
    bool isEquip = false;
    StoreScene *sc = (StoreScene*)m_storeScene;
    ItemBuyLayer *buyLayer = (ItemBuyLayer*)node;
    if (buyLayer->m_itemIt.type==2) {
        for (int i=1; i<6; i++) {
            WeaponSlotNode *wNode = (WeaponSlotNode*)sc->getChildByTag((SlotFlag)i);
            if (wNode->m_slotType == unlock && (wNode->m_itemInfo.number==0 || wNode->m_itemInfo.imageFile=="")) {
                buyLayer->removeFromParent();
                wNode->equipItem(buyLayer->m_itemIt);
                isEquip = true;
                this->removeItem(buyLayer->m_itemIt);
                
                DBUtil::initDB("MyGameInfo.db");
                std::string updateNumberSql = "update my_item set equipSlotIndex = "+CCString::createWithFormat("%d",i)->m_sString+" where itemid = "+CCString::createWithFormat("%d",buyLayer->m_itemIt.id)->m_sString+" and type = "+CCString::createWithFormat("%d",buyLayer->m_itemIt.type)->m_sString+";";
                DBUtil::updateData(updateNumberSql);
                DBUtil::closeDB();
                
                //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("armourshop.wav");
                return;
            }
        }
        
        if (!isEquip) {
            CCCallFuncN	*alertCallback = CCCallFuncN::create(this,callfuncN_selector(StashNode::alertShow));
            alertCallback->execute();
        }
    }else{
        ItemSlotNode *iNode = (ItemSlotNode*)sc->iNode;
        iNode->equipWeapon(buyLayer->m_itemIt);
        this->removeItem(buyLayer->m_itemIt);
        buyLayer->removeFromParent();
        //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("armourshop.wav");
    }
    
}

void StashNode::alertShow()
{
   CCMessageBox("您没有空余的背包！", "失败");
}
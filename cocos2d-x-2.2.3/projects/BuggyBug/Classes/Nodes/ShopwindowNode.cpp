//
//  ShopwindowNode.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-16.
//
//

#include "ShopwindowNode.h"
#include "UITools.h"
#include "AllDefines.h"
#include "ShopwindowCell.h"
#include "ItemsForShopwindowNode.h"
#include "StoreScene.h"
#include "WeaponSlotNode.h"
#include "SimpleAudioEngine.h"
#include "DBUtil.h"
ShopwindowNode::ShopwindowNode(void)
:m_bgSprite(NULL)
{
	this->ignoreAnchorPointForPosition(false);
}


ShopwindowNode::~ShopwindowNode(void)
{

}

bool ShopwindowNode::init()
{
    dataArr = CCArray::create();
    dataArr->retain();
//    dataArr->addObject(CCString::create("weapon1.png"));
//    dataArr->addObject(CCString::create("weapon2.png"));
//    dataArr->addObject(CCString::create("weapon3.png"));
//    dataArr->addObject(CCString::create("weapon4.png"));
//    dataArr->addObject(CCString::create("weapon5.png"));
//    dataArr->addObject(CCString::create("weapon6.png"));
//    dataArr->addObject(CCString::create("weapon7.png"));
//    dataArr->addObject(CCString::create("weapon8.png"));
//    dataArr->addObject(CCString::create("weapon9.png"));
//    dataArr->addObject(CCString::create("weapon10.png"));
//    dataArr->addObject(CCString::create("weapon11.png"));
    
    UILoaderItem *itemLoader = (UILoaderItem*)ConfigCache::sharedConfigCache()->getConfig(xml_type_item);
    ItemStruct item = itemLoader->getRole(1);
    ItemPropertyIt itemIt;
    for (itemIt = item.attributes.begin(); itemIt != item.attributes.end(); ++itemIt) {
        CCDictionary *dic = CCDictionary::create();
        dic->setObject(CCString::createWithFormat("%d",itemIt->second.id), "id");
        dic->setObject(CCString::createWithFormat("%s",itemIt->second.imageFile.c_str()), "image");
        dic->setObject(CCString::createWithFormat("%s",itemIt->second.price.c_str()), "price");
        dic->setObject(CCString::createWithFormat("%s",itemIt->second.describe.c_str()), "describe");
        dic->setObject(CCString::createWithFormat("%d",itemIt->second.type), "type");
        dic->setObject(CCString::createWithFormat("%d",0), "number");
        dataArr->addObject(dic);
    }
    
    tableview = CCTableView::create(this, CCSizeMake(442, 200));
    tableview->setDirection(kCCScrollViewDirectionVertical); //设置tableview的方向是竖直方向，当然也有水平方向
    tableview->setDelegate(this);
    tableview->setVerticalFillOrder(kCCTableViewFillTopDown);// 设置tableview cell的index排列，这里设置是从上到下变大，当然也可以从下到上变大。
    tableview->setPosition(ccp(100,100));
    this->tableview->setTouchPriority(-1028);
    this->addChild(tableview);
    this->tableview->reloadData();
    
	return true;
}

ShopwindowNode* ShopwindowNode::create( const char *bgImg )
{
    UITouchSprite *sprite = UITouchSprite::create(bgImg,bgImg);
	//CCSprite *sprite = UITools::createSprite(bgImg);
    //CCSprite *sprite = CCSprite::create(bgImg);
	return ShopwindowNode::create(sprite);
}

ShopwindowNode* ShopwindowNode::create( CCSprite *bgSprite )
{
	ShopwindowNode *node = new ShopwindowNode;
	node->initWithSprite(bgSprite);
	node->autorelease();
	return node;
}

ShopwindowNode* ShopwindowNode::create( CCSize &size )
{
	ShopwindowNode *node = new ShopwindowNode;
	node->initWithSize(size);
	node->autorelease();
	return node;
}

void ShopwindowNode::setBackground( CCSprite *bgSprite )
{
    weapBut = UITouchSprite::create("nav-unselected.png", "nev-selected.png");
    weapBut->setTag(100);
    weapBut->setPosition(ccp(bgSprite->getContentSize().width* 0.34, CCScreenHeight));
    weapBut->setTouchEnabled(true);
    weapBut->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ShopwindowNode::selectItemAction)));
    this->addChild(weapBut);
    CCSprite *weapIcon = UITools::createSprite("icon-weapons.png");
    weapIcon->setPosition(ccp(weapBut->getContentSize().width * .5,weapBut->getContentSize().height *.5));
    weapBut->addChild(weapIcon);
    
    itemBut = UITouchSprite::create("nav-unselected.png", "nev-selected.png");
    itemBut->setTag(200);
    itemBut->setPosition(ccp(bgSprite->getContentSize().width* 0.5, CCScreenHeight));
    itemBut->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ShopwindowNode::selectItemAction)));
    itemBut->setTouchEnabled(true);
    this->addChild(itemBut);
    CCSprite *itemIcon = UITools::createSprite("icon-items.png");
    itemIcon->setPosition(ccp(weapBut->getContentSize().width * .5,weapBut->getContentSize().height *.5));
    itemBut->addChild(itemIcon);
    
    goldBut = UITouchSprite::create("nav-unselected.png", "nev-selected.png");
    goldBut->setTag(300);
    goldBut->setPosition(ccp(bgSprite->getContentSize().width* 0.66, CCScreenHeight));
    goldBut->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ShopwindowNode::selectItemAction)));
    goldBut->setTouchEnabled(true);
    this->addChild(goldBut);
    CCSprite *goldIcon = UITools::createSprite("icon-coins.png");
    goldIcon->setPosition(ccp(weapBut->getContentSize().width * .5,weapBut->getContentSize().height *.5));
    goldBut->addChild(goldIcon);
    
	bgSprite->setPosition(ccp(bgSprite->getContentSize().width * .5,bgSprite->getContentSize().height *.5));
	this->addChild(bgSprite);
	m_bgSprite = bgSprite;
}

void ShopwindowNode::selectItemAction(CCNode *node)
{
    switch (node->getTag()) {
        case 100:
        {
            dataArr->removeAllObjects();
            UILoaderItem *itemLoader = (UILoaderItem*)ConfigCache::sharedConfigCache()->getConfig(xml_type_item);
            ItemStruct item = itemLoader->getRole(1);
            ItemPropertyIt itemIt;
            for (itemIt = item.attributes.begin(); itemIt != item.attributes.end(); ++itemIt) {
                CCDictionary *dic = CCDictionary::create();
                dic->setObject(CCString::createWithFormat("%d",itemIt->second.id), "id");
                dic->setObject(CCString::createWithFormat("%s",itemIt->second.imageFile.c_str()), "image");
                dic->setObject(CCString::createWithFormat("%s",itemIt->second.price.c_str()), "price");
                dic->setObject(CCString::createWithFormat("%s",itemIt->second.describe.c_str()), "describe");
                dic->setObject(CCString::createWithFormat("%d",itemIt->second.type), "type");
                dic->setObject(CCString::createWithFormat("%d",0), "number");
                dataArr->addObject(dic);
            }
            tableview->reloadData();
        }
            break;
        case 200:
        {
            dataArr->removeAllObjects();
            UILoaderItem *itemLoader = (UILoaderItem*)ConfigCache::sharedConfigCache()->getConfig(xml_type_item);
            ItemStruct item = itemLoader->getRole(2);
            ItemPropertyIt itemIt;
            for (itemIt = item.attributes.begin(); itemIt != item.attributes.end(); ++itemIt) {
                CCDictionary *dic = CCDictionary::create();
                dic->setObject(CCString::createWithFormat("%d",itemIt->second.id), "id");
                dic->setObject(CCString::createWithFormat("%s",itemIt->second.imageFile.c_str()), "image");
                dic->setObject(CCString::createWithFormat("%s",itemIt->second.price.c_str()), "price");
                dic->setObject(CCString::createWithFormat("%s",itemIt->second.describe.c_str()), "describe");
                dic->setObject(CCString::createWithFormat("%d",itemIt->second.type), "type");
                dic->setObject(CCString::createWithFormat("%d",0), "number");
                dataArr->addObject(dic);
            }
            tableview->reloadData();
        }
            break;
        case 300:
        {
            dataArr->removeAllObjects();
            tableview->reloadData();
        }
            break;
            
        default:
            break;
    }
}

bool ShopwindowNode::initWithFile( const char *bgImg )
{
	CCSprite *sprite = UITools::createSprite(bgImg);
	CCSize size = sprite->getContentSize();
	setBackground(sprite);
	return initWithSize(size);
}

bool ShopwindowNode::initWithSprite( CCSprite *sprite )
{
	CCSize size = sprite->getContentSize();
    size.height = size.height+67;
	setBackground(sprite);
	return initWithSize(size);
}

bool ShopwindowNode::initWithSize( CCSize &size )
{
	this->setAnchorPoint(ccp(.5,.5));
	this->setContentSize(size);
    
	return init();
}

void ShopwindowNode::tableCellTouched(CCTableView *table, CCTableViewCell *cell)
{
    //CCLOG("you touch cell index = %u",cell->getIdx());
}

CCSize ShopwindowNode::tableCellSizeForIndex(CCTableView *table, unsigned int idx)
{
    return CCSizeMake(442, 100);
}

unsigned int ShopwindowNode::numberOfCellsInTableView(CCTableView *table)
{
    int row;
    CCLOG("%d",dataArr->count()%4);
    if (dataArr->count()%4==0) {
        row = dataArr->count()/4;
    }else{
        row = dataArr->count()/4+1;
    }
    return row;
}

CCTableViewCell* ShopwindowNode::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new ShopwindowCell();
        cell->autorelease();
    }
    //cell->removeAllChildrenWithCleanup(true);
    CCArray *arr = cell->getChildren();
    if (arr) {
        for (int i=0;i<arr->count();i++) {
            ItemsForShopwindowNode *itemNode = (ItemsForShopwindowNode*)arr->objectAtIndex(i);
            itemNode->m_bgSprite->setTouchEnabled(false);
            itemNode->m_priceSprite->setTouchEnabled(false);
        }
    }
    
    cell->removeAllChildrenWithCleanup(true);
    for (int i=idx*4; i<idx*4+4; i++) {
        if (i<dataArr->count()) {
            CCDictionary *dic = (CCDictionary*)dataArr->objectAtIndex(i);
            ItemsForShopwindowNode *sprite1 = ItemsForShopwindowNode::create(dic);
            
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
            switch (idx*4+4-i) {
                case 4:
                    sprite1->setPosition(ccp(45, 15));
                    break;
                case 3:
                    sprite1->setPosition(ccp(140, 15));
                    break;
                case 2:
                    sprite1->setPosition(ccp(240, 15));
                    break;
                case 1:
                    sprite1->setPosition(ccp(330, 15));
                    break;
                default:
                    break;
            }
            sprite1->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ShopwindowNode::showInfoAction)));
            cell->addChild(sprite1);
        }
    }
    return cell;
}

void ShopwindowNode::showInfoAction(CCNode *node)
{
    StoreScene *sc = (StoreScene*)m_storeScene;
    int currMoney = std::atoi(sc->stNode->numLabel->getString());
    
    ItemsForShopwindowNode *shopwindows = (ItemsForShopwindowNode*)node;
    //ItemPropertyStruct itemInfo = shopwindows->itemInfo;
    
    m_itemBuyLayer = ItemBuyLayer::create(shopwindows->itemInfo);
    m_itemBuyLayer->setVisible(true);
    m_itemBuyLayer->setClickCallback(CCCallFuncN::create(this,callfuncN_selector(ShopwindowNode::buyAction)));
    m_storeScene->addChild(m_itemBuyLayer);
    m_itemBuyLayer->show();
    
    m_itemBuyLayer->m_moneyLabel->setString(CCString::createWithFormat("%d",currMoney)->getCString());
}

void ShopwindowNode::buyAction(CCNode *node)
{
    StoreScene *sc = (StoreScene*)m_storeScene;
    CCLOG("%s",sc->stNode->numLabel->getString());
    ItemBuyLayer *buyLayer = (ItemBuyLayer*)node;
    if(!sc->stNode->isMoney(buyLayer->m_itemIt.price.c_str()))
    {
        CCMessageBox("您的金币不足！", "购买失败");
    }else{
        bool isEquip = false;
        for (int i=1; i<6; i++) {
            WeaponSlotNode *wNode = (WeaponSlotNode*)sc->getChildByTag((SlotFlag)i);
            if (wNode->m_itemInfo.id == buyLayer->m_itemIt.id && wNode->m_itemInfo.type == buyLayer->m_itemIt.type) {
                int currMoney = std::atoi(wNode->numLabel->getString());
                int updateMoney = currMoney+1;
                wNode->numLabel->setString(CCString::createWithFormat("%d",updateMoney)->getCString());
                wNode->m_itemInfo.number = updateMoney;
                isEquip = true;
                
                sc->stNode->updateMoney(buyLayer->m_itemIt.price.c_str());
                buyLayer->number = buyLayer->number+1;
                buyLayer->m_numberLabel->setString(CCString::createWithFormat("%d",buyLayer->number)->getCString());
                
                DBUtil::initDB("MyGameInfo.db");
                std::string updateNumberSql = "update my_item set number = "+CCString::createWithFormat("%d",updateMoney)->m_sString+" where itemid = "+CCString::createWithFormat("%d",wNode->m_itemInfo.id)->m_sString+" and type = "+CCString::createWithFormat("%d",wNode->m_itemInfo.type)->m_sString+";";
                DBUtil::updateData(updateNumberSql);
                DBUtil::closeDB();
                
                //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("CoinI.wav");
                return;
            }
        }
        if ((sc->iNode->itemInfo1.id == buyLayer->m_itemIt.id || sc->iNode->itemInfo2.id == buyLayer->m_itemIt.id || sc->iNode->itemInfo3.id == buyLayer->m_itemIt.id) && buyLayer->m_itemIt.type==1) {
            CCMessageBox("该武器已经购买过了！", "购买失败");
            isEquip = true;
            
//            buyLayer->number = 0;
//            buyLayer->m_numberLabel->setString(CCString::createWithFormat("%d",buyLayer->number)->getCString());
        }
        if (!isEquip) {
            if (sc->stNode->addItem(buyLayer->m_itemIt)) {
                sc->stNode->updateMoney(buyLayer->m_itemIt.price.c_str());
                
                buyLayer->number = buyLayer->number+1;
                buyLayer->m_numberLabel->setString(CCString::createWithFormat("%d",buyLayer->number)->getCString());
                //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("CoinI.wav");
            }else{
                
//                buyLayer->number = 0;
//                buyLayer->m_numberLabel->setString(CCString::createWithFormat("%d",buyLayer->number)->getCString());
            }
        }
        
        buyLayer->runSpiderWiggleSequence(buyLayer->itemSpriteIcon);
        
        int currMoney = std::atoi(sc->stNode->numLabel->getString());
        buyLayer->m_moneyLabel->setString(CCString::createWithFormat("%d",currMoney)->getCString());
    }
}
//
//  StoreScene.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-15.
//
//

#ifndef __BuggyBug__StoreScene__
#define __BuggyBug__StoreScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "UITouchSprite.h"
#include "ItemBuyLayer.h"
#include "StashNode.h"
#include "ShopwindowNode.h"
#include "ItemSlotNode.h"
USING_NS_CC;
USING_NS_CC_EXT;
class StoreScene : public CCLayer
{
public:
    StoreScene(void);
	~StoreScene(void);
    
    virtual bool init();
    
    void onEnter();
    
	void onExit();
    
    void setBackgroundWall();
    
    void eyesBlinkAction();
    
    void setWeaponSlot();
    
    void setItemSlot();
    
    void setShopwindow();
    
    void setStashNode();
    
    void initDB();
    
    void exitAction(CCNode *node);
    
    void buyAction(CCNode *node);
    
    void runSpiderWiggleSequence(UITouchSprite *spider);
    
    static CCScene* scene();
    
    CREATE_FUNC(StoreScene);
    
public:
    StashNode *stNode;
    ShopwindowNode *sNode;
    ItemSlotNode *iNode;
    
private:
    CCSprite *m_bgSprite;
    CCSprite *eyes;
    UITouchSprite *exitBut;
    ItemBuyLayer * m_itemBuyLayer;
};
#endif /* defined(__BuggyBug__StoreScene__) */

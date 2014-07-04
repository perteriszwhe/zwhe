//
//  ItemSlotNode.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-19.
//
//

#ifndef __BuggyBug__ItemSlotNode__
#define __BuggyBug__ItemSlotNode__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "UITouchSprite.h"
#include "ItemBuyLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;
class ItemSlotNode:public CCNode
{
public:
    ItemSlotNode(void);
	virtual ~ItemSlotNode(void);
    virtual void onEnter();
    virtual void onExit();
    virtual bool initWithSize(CCSize &size);
    virtual bool initWithSprite(UITouchSprite *sprite);
	virtual bool init();
    
    static ItemSlotNode* create(CCSize &size);
	static ItemSlotNode* create(UITouchSprite *bgSprite);
	static ItemSlotNode* create(const char *bgImg);
    
    void setBackground(UITouchSprite *bgSprite);
    void lastAction(CCNode *node);
    void nextAction(CCNode *node);
    void downaAction(CCNode *node);
    void equipWeapon(ItemPropertyStruct itemInfo);
    void showWeapon(int index);
    void loadEquipWeapon(CCArray *itemArray);
    
public:
    UITouchSprite *m_bgSprite;
    UITouchSprite *lastBut;
    UITouchSprite *nextBut;
    ItemPropertyStruct itemInfo1;
    ItemPropertyStruct itemInfo2;
    ItemPropertyStruct itemInfo3;
    
    ItemPropertyStruct currItemInfo;
    
    CCSprite *itemSprite1;
    CCSprite *itemSprite2;
    CCSprite *itemSprite3;
    
    CCLayer * m_storeScene;
    
    int currIndex;
};

#endif /* defined(__BuggyBug__ItemSlotNode__) */

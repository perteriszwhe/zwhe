//
//  WeaponSlotNode.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-16.
//
//

#ifndef __BuggyBug__WeaponSlotNode__
#define __BuggyBug__WeaponSlotNode__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConfigCache.h"
#include "UITouchSprite.h"
USING_NS_CC;
USING_NS_CC_EXT;
enum SlotType
{
    lock=1,
    unlock,
};

enum SlotFlag
{
    slotOne=1,
    slotTwo,
    slotThree,
    slotFour,
    slotFive,
};
class WeaponSlotNode: public CCNode
{
public:
    WeaponSlotNode(void);
	virtual ~WeaponSlotNode(void);
    virtual void onEnter();
    virtual void onExit();
    virtual bool initWithSize(CCSize &size);
    virtual bool initWithFile(const char *bgImg);
    virtual bool initWithSprite(UITouchSprite *sprite);
	virtual bool init();
    
    static WeaponSlotNode* create(SlotType slotType,SlotFlag slotFlag);
    static WeaponSlotNode* create(CCSize &size);
	static WeaponSlotNode* create(UITouchSprite *bgSprite);
	static WeaponSlotNode* create(const char *bgImg);
    
    void setBackground(UITouchSprite *bgSprite);
    
    void setSlotType(SlotType slotType);
    void setSlotFlag(SlotFlag slotFlag);
    void equipItem(ItemPropertyStruct itemInfo);
    
    
    void runSpiderWiggleSequence(UITouchSprite *spider);
    
    void unlockAction(CCNode *node);
    
public:
    UITouchSprite *m_bgSprite;
    CCLabelTTF *numLabel;
    SlotType m_slotType;
    SlotFlag m_slotFlag;
    ItemPropertyStruct m_itemInfo;
    CCSprite *itemSprite;
    CCLayer * m_storeScene;
};
#endif /* defined(__BuggyBug__WeaponSlotNode__) */

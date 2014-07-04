//
//  WeaponSlot.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-6-11.
//
//

#ifndef __BuggyBug__WeaponSlot__
#define __BuggyBug__WeaponSlot__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ScoresManager.h"
#include "UITouchSprite.h"
USING_NS_CC;
USING_NS_CC_EXT;
class WeaponSlot:public CCNode
{
public:
    WeaponSlot(void);
	virtual ~WeaponSlot(void);
    virtual bool initWithSize(CCSize &size);
    virtual bool initWithSprite(UITouchSprite *sprite);
	virtual bool init();
    
    static WeaponSlot* create(CCSize &size);
	static WeaponSlot* create(UITouchSprite *bgSprite);
	static WeaponSlot* create(const char *bgImg);
    
    void setBackground(UITouchSprite *bgSprite);
    void downaAction(CCNode *node);
    void showWeapon(int index);
    void loadEquipWeapon(CCArray *itemArray);
    
public:
    UITouchSprite *m_bgSprite;
    ItemPropertyStruct itemInfo1;
    ItemPropertyStruct itemInfo2;
    ItemPropertyStruct itemInfo3;
    
    ItemPropertyStruct currItemInfo;
    
    CCSprite *itemSprite1;
    CCSprite *itemSprite2;
    CCSprite *itemSprite3;
    
    CCLayer * m_storeScene;
    
    int currIndex;
    
private:
    CCSprite *indexSpriteOne;
    CCSprite *indexSpriteTwo;
    CCSprite *indexSpriteThree;
};

#endif /* defined(__BuggyBug__WeaponSlot__) */

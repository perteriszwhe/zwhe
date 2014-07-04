//
//  ItemSlot.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-6-4.
//
//

#ifndef __BuggyBug__ItemSlot__
#define __BuggyBug__ItemSlot__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCSkeletonAnimation.h"
#include "ScoresManager.h"
USING_NS_CC;
USING_NS_CC_EXT;
enum SlotIndex
{
    sloteOne=1,
    sloteTwo,
    sloteThree,
    sloteFour,
    sloteFive,
};
class ItemSlot:public CCSkeletonAnimation, public CCTargetedTouchDelegate
{
protected:
    SlotIndex m_slotIndex;
    
public:
    virtual ~ItemSlot();
    
    static ItemSlot* createWithType(SlotIndex sloteIndex);
    
    static ItemSlot* createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale = 1);
    ItemSlot (const char* skeletonDataFile, const char* atlasFile, float scale = 1);
    
    static ItemSlot* createWithData (SkeletonData* skeletonData);
    ItemSlot (SkeletonData* skeletonData);
    
    virtual void onEnter();
    
    virtual void onExit();
    
    virtual void onEnterTransitionDidFinish();
    
    virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
    
	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );
    
public:
    virtual void setSlotIndex(SlotIndex sloteIndex);
    
    void registerWithTouchDispatcher(void);
    
    void setTouchEnabled( bool enable );
    
    bool getTouchEnabled() const{ return m_isTouchEnabled; }
    
    virtual void initSelf();
    
    void skillCoolDownCallBack(CCNode *node);
    
    void startCD();
    
    void equipItem(ItemPropertyStruct itemInfo);
    
    void cdTimeAction();
    
public:
    CCProgressTimer * mProgressTimer;
    CCLabelTTF *numberLabel;
    CCLabelTTF *cdTimeLabel;
    ItemPropertyStruct m_itemInfo;
    CCSprite *itemSprite;
    int m_nPriority = -90;
    
private:
	bool isTouchMe(CCTouch* pTouch);
    
private:
	bool			m_isTouchEnabled = false;
};
#endif /* defined(__BuggyBug__ItemSlot__) */

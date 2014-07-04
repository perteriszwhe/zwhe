//
//  ItemBuyLayer.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-18.
//
//

#ifndef __BuggyBug__ItemBuyLayer__
#define __BuggyBug__ItemBuyLayer__

#include "cocos2d.h"
#include "ConfigCache.h"
#include "UITouchSprite.h"
USING_NS_CC;
class ItemBuyLayer:public CCLayer
{
public:
    CREATE_FUNC(ItemBuyLayer);
    
	virtual bool init();
	ItemBuyLayer(void);
	~ItemBuyLayer(void);
    static ItemBuyLayer* create(ItemPropertyStruct itemIt);
    virtual bool initWithFile();
    virtual bool initWithInfo(ItemPropertyStruct itemIt);
    
    void closeWindow(CCNode *node);
    void buyAction(CCNode *node);
    void equipAction(CCNode *node);
	void show();
	void hide();
    virtual void onEnter();
    virtual void onExit();
    void setClickCallback(CCCallFuncN *callback);
    void runSpiderWiggleSequence(CCSprite *spider);
public:
    UITouchSprite *closeBut;
    UITouchSprite *buyBut;
    UITouchSprite *equipBut;
    ItemPropertyStruct m_itemIt;
    CCCallFuncN	*m_ClickCallback;
    CCSprite *itemSpriteIcon;
    CCLabelTTF *m_moneyLabel;
    CCLabelTTF *m_numberLabel;
    int number;
};

#endif /* defined(__BuggyBug__ItemBuyLayer__) */

//
//  ItemsForShopwindowNode.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-18.
//
//

#ifndef __BuggyBug__ItemsForStashNode__
#define __BuggyBug__ItemsForStashNode__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "UITouchSprite.h"
#include "ItemBuyLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ItemsForStashNode: public CCNode
{
public:
    ItemsForStashNode(void);
	virtual ~ItemsForStashNode(void);
    virtual void onEnter();
    virtual void onExit();
    virtual bool initWithSize(CCSize &size);
    virtual bool initWithFile(const char *bgImg);
    virtual bool initWithSprite(UITouchSprite *sprite,UITouchSprite *priceSprite);
	virtual bool init();
    virtual bool initWithInfo(CCDictionary *infoDic);
    
    static ItemsForStashNode* create(CCSize &size);
	static ItemsForStashNode* create(UITouchSprite *bgSprite,UITouchSprite *priceSprite);
	static ItemsForStashNode* create(const char *bgImg,int money);
    static ItemsForStashNode* create(CCDictionary *infoDic);
    
    void setBackground(UITouchSprite *bgSprite,UITouchSprite *priceSprite );
    void showInfoAction(CCNode *node);
    void setClickCallback(CCCallFuncN *callback);
public:
    UITouchSprite *m_bgSprite;
    UITouchSprite *m_priceSprite;
    CCSprite *m_icoSprite;
    CCLabelTTF *m_moneyLabel;
    ItemBuyLayer * m_itemBuyLayer;
    CCLayer * m_storeScene;
    CCCallFuncN	*m_ClickCallback;
    ItemPropertyStruct itemInfo;
};

#endif /* defined(__BuggyBug__ItemsForStashNode__) */

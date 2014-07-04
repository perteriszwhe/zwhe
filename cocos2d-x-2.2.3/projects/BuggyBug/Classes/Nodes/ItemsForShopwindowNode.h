//
//  ItemsForShopwindowNode.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-18.
//
//

#ifndef __BuggyBug__ItemsForShopwindowNode__
#define __BuggyBug__ItemsForShopwindowNode__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "UITouchSprite.h"
#include "ItemBuyLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ItemsForShopwindowNode: public CCNode
{
public:
    ItemsForShopwindowNode(void);
	virtual ~ItemsForShopwindowNode(void);
    virtual void onEnter();
    virtual void onExit();
    virtual bool initWithSize(CCSize &size);
    virtual bool initWithFile(const char *bgImg);
    virtual bool initWithSprite(UITouchSprite *sprite,UITouchSprite *priceSprite);
    virtual bool initWithInfo(CCDictionary *infoDic);
	virtual bool init();
    
    static ItemsForShopwindowNode* create(CCSize &size);
	static ItemsForShopwindowNode* create(UITouchSprite *bgSprite,UITouchSprite *priceSprite);
	static ItemsForShopwindowNode* create(const char *bgImg,int money);
    static ItemsForShopwindowNode* create(CCDictionary *infoDic);
    
    void setBackground(UITouchSprite *bgSprite,UITouchSprite *priceSprite );
    void showInfoAction(CCNode *node);
    void setClickCallback(CCCallFuncN *callback);
public:
    UITouchSprite *m_bgSprite;
    UITouchSprite *m_priceSprite;
    CCSprite *m_icoSprite;
    CCLabelTTF *m_moneyLabel;
    ItemBuyLayer * m_itemBuyLayer;
    CCCallFuncN	*m_ClickCallback;
    ItemPropertyStruct itemInfo;
};

#endif /* defined(__BuggyBug__ItemsForShopwindowNode__) */

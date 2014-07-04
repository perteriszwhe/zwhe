//
//  StashNode.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-16.
//
//

#ifndef __BuggyBug__StashNode__
#define __BuggyBug__StashNode__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "UITouchSprite.h"
#include "ItemBuyLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;
class StashNode: public CCNode,public CCTableViewDelegate,public CCTableViewDataSource
{
public:
    StashNode(void);
	virtual ~StashNode(void);
    virtual bool initWithSize(CCSize &size);
    virtual bool initWithFile(const char *bgImg);
    virtual bool initWithSprite(CCSprite *sprite);
	virtual bool init();
    
    static StashNode* create(CCSize &size);
	static StashNode* create(CCSprite *bgSprite);
	static StashNode* create(const char *bgImg);
    
    void setBackground(CCSprite *bgSprite);
    void showInfoAction(CCNode *node);
    bool updateMoney(const char *money);
    bool isMoney(const char *money);
    bool addItem(ItemPropertyStruct itemIt);
    void removeItem(ItemPropertyStruct itemIt);
    void equipAction(CCNode *node);
    void alertShow();
    void loadMyData(CCArray *itemArray);
    
public:
    CCSprite *m_bgSprite;
    CCTableView *tableview;
    CCLayer * m_storeScene;
    ItemBuyLayer * m_itemBuyLayer;
    CCLabelTTF *numLabel;
    CCArray *dataArr;
    
private:
    //触摸到某个cell的事件
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    //定制每个cell的size
    virtual CCSize tableCellSizeForIndex(CCTableView *table, unsigned int idx);
    //定制每个cell的内容
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    //确定这个tableview的cell行数
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
    //由于CCTableView是继承CCScrollView，所以要继承这两个方法
    virtual void scrollViewDidScroll(CCScrollView* view) {}
    virtual void scrollViewDidZoom(CCScrollView* view) {}
};

#endif /* defined(__BuggyBug__StashNode__) */

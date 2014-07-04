#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class HelloWorld : public CCLayer,public CCTableViewDelegate,public CCTableViewDataSource
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void menuCallBack(cocos2d::CCObject *pSender);
    
    
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
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__

//
//  CountDownLayer.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-4-28.
//
//

#ifndef __BuggyBug__CountDownLayer__
#define __BuggyBug__CountDownLayer__

#include "cocos2d.h"
USING_NS_CC;
class CountDownLayer : public CCLayer
{
private:
	CCCallFuncN		*m_allFinishCallback;
    int showTime;
    
public:
//    CountDownLayer(void);
//	~CountDownLayer(void);
    
    virtual bool init();
    
    virtual void onEnterTransitionDidFinish();
    
    virtual void onEnter();
    
    static CountDownLayer* create(CCCallFuncN *callback);
    
    bool initCallback(CCCallFuncN *callback);
    
	void setAllFinishCallback(CCCallFuncN *callback);
    
    void startCountDown();
    
    void countDownEndCallBack(CCObject* pSender);
    
    CREATE_FUNC(CountDownLayer);
    
public:
    CCLabelTTF* cakeFenshuLabel;
    CCLabelTTF* myFenshuLabel;
    CCLabelTTF* boCiLabel;
};
#endif /* defined(__BuggyBug__CountDownLayer__) */

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "NormalAnt.h"
#include "NormalFasterAnt.h"
#include "CCSkeletonAnimation.h"
#include "pauseDialog.h"
USING_NS_CC;
USING_NS_CC_EXT;

class HelloWorld : public CCLayer
{
private:
    NormalAnt * _normalAnt;
    NormalFasterAnt * _fasterAnt;
    int showTime;
    CCLabelTTF* pLabel;
    CCSkeletonAnimation* skeletonNode;
    Atlas* atlas;
    
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void CallFucnCallback1(CCObject* pSender);
    
    void menuSetVisableFalse(CCObject* pSender);
    void menuSetVisableFalse2(CCObject* pSender);
    
    
	int num;
	void myupdate(float dt);
    void myupdate2(float dt);
    void myupdate3();
    
    int getRand(int start,int end);
    float myRand_0_1(float start,float end);
    
//    virtual void onEnter();
//    virtual void onExit();
//    virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );
//	bool isTouchMe(CCTouch* pTouch,NormalAnt* ant);
    
    // implement the "static node()" method manually
    CCLabelTTF* cakeFenshuLabel;
    CCLabelTTF* myFenshuLabel;
    CCLabelTTF* boCiLabel;
    PauseDialog * m_pauseDialog;
    bool isOver;
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__

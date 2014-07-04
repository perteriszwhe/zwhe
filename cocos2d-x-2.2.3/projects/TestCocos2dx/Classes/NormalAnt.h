//
//  NormalAnt.h
//  TestCocos2dx
//
//  Created by He Zhiwei on 14-4-10.
//
//

#ifndef __TestCocos2dx__NormalAnt__
#define __TestCocos2dx__NormalAnt__

#include <iostream>
#include "cocos2d.h"
#include "AppMacros.h"
#include "cocos-ext.h"
#include "CCSkeletonAnimation.h"
#include <spine/CCSkeleton.h>
USING_NS_CC;
USING_NS_CC_EXT;



typedef enum {
    kRoleDirectionRight,
    kRoleDirectionLeft,
}RoleDirection;

typedef enum {
    kRoleStateNone=0,
    kRoleStateIdle,
    kRoleStateWalk,
    kRoleStateAttack,
    kRoleStateHurt,
    kRoleStateKnockedOut
}RoleState;

class NormalAnt:public CCSkeletonAnimation, public CCTargetedTouchDelegate {
//private:
//    bool isAlive;           //是否存活
protected:
    cocos2d::CCArray * arrayActions;
    RoleDirection roleDirection;
    
    int totalBlood;         //总血
    //int currentBlood;       //当前血
    //int damage;             //攻击力量，每次攻击打下多少血
    float speed;           //移动速度
public:
    virtual ~NormalAnt();
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );
    
	static NormalAnt* createWithFile (const char* skeletonDataFile, Atlas* atlas, float scale = 1);
	NormalAnt (const char* skeletonDataFile, Atlas* atlas, float scale = 1);
    
    static NormalAnt* createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale = 1);
    NormalAnt (const char* skeletonDataFile, const char* atlasFile, float scale = 1);

    CCPoint startPoint;
    virtual void initActions();
    virtual void initSelf();
    virtual void onEnterTransitionDidFinish();
    void starAction();
    void starMove(CCPoint point,float time);
    void endMove(CCPoint point,float time);
    void CallFucnCallback1(CCObject* pSender);
    void CallFucnCallback2(CCObject* pSender);
    void CallFucnCallbackLizi(CCObject* pSender);
    void checkBox();   //注意参数类型
    
    void setDirection(RoleDirection rDirection);
    RoleDirection getDirection(){return roleDirection;};
    void changeDirection();
    
    RoleState roleState;
    virtual RoleState getState(){ return roleState; }
    virtual void setState(RoleState rState){ roleState=rState; }
    int getRand(int start,int end);
    
private:
	bool isTouchMe(CCTouch* pTouch);
};

#endif /* defined(__TestCocos2dx__NormalAnt__) */

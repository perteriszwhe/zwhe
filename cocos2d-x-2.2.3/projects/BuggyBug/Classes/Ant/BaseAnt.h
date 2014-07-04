//
//  BaseAnt.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-4-28.
//
//

#ifndef __BuggyBug__BaseAnt__
#define __BuggyBug__BaseAnt__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCSkeletonAnimation.h"
#include "ScoresManager.h"
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
    kRoleStateDie,
    kRoleStateRun,
    kRoleStateCryRun,
}RoleState;

class BaseAnt:public CCSkeletonAnimation, public CCTargetedTouchDelegate {
protected:
    int totalBlood;         //总血
    int currentBlood;       //当前血
    int damage;             //攻击力量，每次攻击打下多少血
    float goInSpeed;        //默认移动速度
    float comeBackSpeed;    //返回移动速度
    int score;              //分数
    RoleDirection roleDirection; //方向
    RoleState roleState; //状态
    AntType m_antType;
    
 public:
    virtual ~BaseAnt();
    
    static BaseAnt* createWithType(AntType antType);
    
    static BaseAnt* createWithFile (const char* skeletonDataFile, Atlas* atlas, float scale = 1);
	BaseAnt (const char* skeletonDataFile, Atlas* atlas, float scale = 1);
    
    static BaseAnt* createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale = 1);
    BaseAnt (const char* skeletonDataFile, const char* atlasFile, float scale = 1);
    
    static BaseAnt* createWithData (SkeletonData* skeletonData);
    BaseAnt (SkeletonData* skeletonData);
    
    virtual void onEnter();
    
    virtual void onExit();
    
    virtual void onEnterTransitionDidFinish();
    
    virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
    
	virtual void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );
    
public:
    void registerWithTouchDispatcher(void);
    
    void setTouchEnabled( bool enable );
    
    bool getTouchEnabled() const{ return m_isTouchEnabled; }
    
    void checkAntHP();
    
    void setDirection(RoleDirection rDirection);
    
    void changeDirection();
    
    void antMove(CCPoint point,float time);
    
    void MoveToCallFucn(CCObject* pSender);
    
    void AntCryBackCall(CCObject* pSender);
    
    void myUpdate();
    
    virtual void initActions();
    
    virtual void initSelf();
    
    virtual void setAntType(AntType antType);
    
public:
    CCPoint startPoint;
    
    //AntType m_antType;
    
private:
	bool isTouchMe(CCTouch* pTouch);
    
private:
	bool			m_isTouchEnabled = false;
    int             m_nPriority = 0;
};
#endif /* defined(__BuggyBug__BaseAnt__) */

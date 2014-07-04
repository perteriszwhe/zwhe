//
//  PlayLayer.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-27.
//
//

#ifndef __BuggyBug__PlayLayer__
#define __BuggyBug__PlayLayer__

#include "cocos2d.h"
#include "ConfigCache.h"
#include "UITouchSprite.h"

USING_NS_CC;
class PlayLayer : public CCLayer
{
public:
    CREATE_FUNC(PlayLayer);
    
	virtual bool init();
	PlayLayer(void);
	~PlayLayer(void);
    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    static PlayLayer* create(CCArray *weaponArr,CCArray *itemArr);
    virtual bool initTitle();
    virtual bool initItem();
    virtual bool initWeapon();
    void pauseGameAction(CCNode *node);
    virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
public:
    CCSprite *m_TitleBgSprite;
    CCSprite *m_ScoresIcon;
    CCSprite *m_CoinIcon;
    CCSprite *m_HPIcon;
    CCSprite *m_TimeIcon;
    
    CCLabelTTF *m_ScoresLabel;
    CCLabelTTF *m_CoinLabel;
    CCLabelTTF *m_HPLabel;
    CCLabelTTF *m_TimeLabel;
    
    UITouchSprite *pauseBut;
    int m_nPriority = 0;
};

#endif /* defined(__BuggyBug__PlayLayer__) */

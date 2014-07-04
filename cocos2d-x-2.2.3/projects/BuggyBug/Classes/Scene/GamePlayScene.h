//
//  GamePlayScene.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-4-27.
//
//

#ifndef __BuggyBug__GamePlayScene__
#define __BuggyBug__GamePlayScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "AllDefines.h"
#include "CountDownLayer.h"
#include "BaseAnt.h"
#include "PauseDialogLayer.h"
#include "PauseLayer.h"
#include "PlayLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GamePlayScene : public CCLayer {
    
public:
    GamePlayScene(void);
	~GamePlayScene(void);
    
    virtual bool init();
    
    void onEnter();
    
	void onExit();
    
    void setBackground(const char *img);
    
    void setPicnicCloth(const char *img);
    
    void setOther();
    
    void setSweetSprite();
    
    void setPlayLayer();
    
    void countDownEndCallBack(CCNode *node);
    
    void showAntUpdate();
    
    void addOneOfNormalAnt(AntType antType,bool isRand);
    
    void addOneOfSuperAnt(AntType antType,bool isRand);
    
    CCArray* loadLevelData(int level);
    
    static CCScene* scene();
    
    CREATE_FUNC(GamePlayScene);
    
public:
    bool isOver;
    CCLabelTTF* cakeFenshuLabel;
    CCLabelTTF* myFenshuLabel;
    CCLabelTTF* boCiLabel;
    PauseDialogLayer * m_pauseDialog;
    PauseLayer * m_pause;
    PlayLayer *playLayer;
    ItemPropertyStruct m_itemInfo;
    CCCallFuncN  *m_itemClickCallback;
    
private:
	CCSprite *m_bgSprite;
    CountDownLayer *downLayer;
    BaseAnt * _normalAnt;
    Atlas * _atlas;
    SkeletonJson * _skJson;
    SkeletonData * _skData;
    CCArray *arr;
};

#endif /* defined(__BuggyBug__GamePlayScene__) */

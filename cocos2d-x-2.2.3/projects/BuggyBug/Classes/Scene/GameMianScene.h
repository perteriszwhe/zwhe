//
//  GameMianScene.h
//  TestCocos2dx
//
//  Created by He Zhiwei on 14-4-25.
//
//

#ifndef __TestCocos2dx__GameMianScene__
#define __TestCocos2dx__GameMianScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCSkeletonAnimation.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GameMianScene : public CCLayerColor
{
private:
    CCParticleSystemQuad *xiayu;
    CCParticleSystemQuad *xiaxue;
    CCParticleSystemQuad *yezi;
    CCParticleSystemQuad* taiyang;
    
    CCMoveTo* moveTo;
    CCMoveTo* moveTo2;
    
    CCSprite *m_bgSprite01;
    CCSprite *m_bgSprite02;
    CCSprite *m_bgSprite03;
    CCSprite *m_bgSprite04;
    
    void taiyangHideCallBack();
public:
	virtual bool init();
    CCSkeletonAnimation * skeletonNode;
    CCSkeletonAnimation * skeletonNode2;
    CCSkeletonAnimation * skeletonNode3;
    static CCScene* scene();
    void addAnt();
    void myupdate();
    void CallFucnCallback1(CCObject* pSender);
    void startGame();
    void gotoStore();
    int getRand(int start,int end);
    void setBackground(const char *img);
    
    CREATE_FUNC(GameMianScene);
};

#endif /* defined(__TestCocos2dx__GameMianScene__) */

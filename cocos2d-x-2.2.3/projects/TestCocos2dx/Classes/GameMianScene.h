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
    int getRand(int start,int end);
    
    CREATE_FUNC(GameMianScene);
};

#endif /* defined(__TestCocos2dx__GameMianScene__) */

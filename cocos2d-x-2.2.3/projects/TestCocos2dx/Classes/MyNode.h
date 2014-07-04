//
//  MyNode.h
//  TestCocos2dx
//
//  Created by He Zhiwei on 14-4-15.
//
//

#ifndef __TestCocos2dx__MyNode__
#define __TestCocos2dx__MyNode__

#include <iostream>
#include "cocos2d.h"
#include "AppMacros.h"
#include "cocos-ext.h"
#include "CCSkeletonAnimation.h"
USING_NS_CC;
USING_NS_CC_EXT;
class MyNode:public CCSkeletonAnimation, public CCTargetedTouchDelegate {
public:
    //MyNode();
    ~MyNode();
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
    
    static MyNode* createWithFile (const char* skeletonDataFile, Atlas* atlas, float scale = 1);
	MyNode (const char* skeletonDataFile, Atlas* atlas, float scale = 1);
    
    //CREATE_FUNC(MyNode);
};
#endif /* defined(__TestCocos2dx__MyNode__) */

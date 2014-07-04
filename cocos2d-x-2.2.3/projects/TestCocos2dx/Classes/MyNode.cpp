//
//  MyNode.cpp
//  TestCocos2dx
//
//  Created by He Zhiwei on 14-4-15.
//
//

#include "MyNode.h"
//MyNode::MyNode(){
//    
//}

MyNode::~MyNode(){
    
}

MyNode* MyNode::createWithFile (const char* skeletonDataFile, Atlas* atlas, float scale) {
	MyNode* node = new MyNode(skeletonDataFile, atlas, scale);
	node->autorelease();
	return node;
}

MyNode::MyNode (const char* skeletonDataFile, Atlas* atlas, float scale)
: CCSkeletonAnimation(skeletonDataFile, atlas, scale) {
	addAnimationState();
}

void MyNode::onEnter()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCNode::onEnter();
}

void MyNode::onExit()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}

bool MyNode::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCLOG("点击了！！！！");
    //CCDirector* pDirector = CCDirector::sharedDirector();
    //pDirector->getTouchDispatcher()->removeDelegate(this);
    
	return true;
}
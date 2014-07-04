//
//  GameMianScene.cpp
//  TestCocos2dx
//
//  Created by He Zhiwei on 14-4-25.
//
//

#include "GameMianScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
CCScene *GameMianScene::scene() {
    
    CCScene* mScene = CCScene::create();
    
    GameMianScene* mLayer = create();
    
    mScene->addChild(mLayer);
    
    return mScene;
}

bool GameMianScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 0)) )
    {
        return false;
    }
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *logLabel = CCLabelTTF::create("Buggy Bug", "AmericanTypewriter-Bold", 60);
    logLabel->setPosition(ccp(windowSize.width-windowSize.width/2,windowSize.height-70));
    this->addChild(logLabel, 1);
    
    CCMenuItemFont::setFontSize(50);
    CCMenuItemFont * item_restart = CCMenuItemFont::create("PLAY" , this, menu_selector(GameMianScene::startGame));
    CCMenuItemFont::setFontSize(50);
	CCMenu * menu = CCMenu::create(item_restart , NULL);
	menu->setPosition(ccp(windowSize.width-windowSize.width/2,windowSize.height/2-200));
	menu->setTag(200);
	this->addChild(menu);
    
    schedule(schedule_selector(GameMianScene::addAnt),1);
    //schedule(schedule_selector(GameMianScene::myupdate),0.1);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("homebg2.mp3", true);
    
    return true;
}

void GameMianScene::addAnt(){
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    const char * antArra[3];
    antArra[0] = "stronger-and-faster-ant";
    antArra[1] = "basic-ant";
    antArra[2] = "faster-ant";
    
    const char * poseArra[5];
    poseArra[0] = "run & cry";
    poseArra[1] = "walk";
    poseArra[2] = "carrying pose 1";
    poseArra[3] = "carrying pose 2";
    poseArra[4] = "carrying pose 3";
    int i = getRand(0, 2);
    int b = getRand(0, 4);
    CCSkeletonAnimation * skeletonNode4 = CCSkeletonAnimation::createWithFile(CCString::createWithFormat("%s.json",antArra[i])->getCString(), CCString::createWithFormat("%s.atlas",antArra[i])->getCString());
    skeletonNode4->setAnimation(poseArra[b], true,0);
    skeletonNode4->setSkin("male");
    skeletonNode4->setScale(0.5);
	skeletonNode4->setPosition(ccp(windowSize.width-windowSize.width-40, 300));
	addChild(skeletonNode4);
    
    CCMoveTo* moveTo=CCMoveTo::create(8.0f, ccp(windowSize.width+40, 300));
    CCCallFuncN* callBackIdle=CCCallFuncN::create(this, callfuncN_selector(GameMianScene::CallFucnCallback1));
    
    CCArray* actionArray=CCArray::create();
    actionArray->addObject(moveTo);
    actionArray->addObject(callBackIdle);
    
    CCSequence* sequeneAction=CCSequence::create(actionArray);
    skeletonNode4->runAction(sequeneAction);
}

void GameMianScene::CallFucnCallback1(CCObject* pSender)
{
    ((CCSkeletonAnimation*)pSender)->removeFromParent();
}

void GameMianScene::myupdate(){
//    CCLOG("宽度：%f  高度：%f",skeletonNode->boundingBox().size.width,skeletonNode->boundingBox().size.height);
//    CCLOG("X：%f  Y：%f",skeletonNode->boundingBox().origin.x,skeletonNode->boundingBox().origin.y);
//    CCLOG("X：%f  Y：%f",skeletonNode->getPosition().x,skeletonNode->getPosition().y);
    //skeletonNode3->boundingBox();

    
//    CCLOG("宽度：%f  高度：%f",skeletonNode2->cocos2d::CCNode::boundingBox().size.width,skeletonNode2->cocos2d::CCNode::boundingBox().size.height);
//    CCLOG("X：%f  Y：%f",skeletonNode2->cocos2d::CCNode::boundingBox().origin.x,skeletonNode2->cocos2d::CCNode::boundingBox().origin.y);
//    CCLOG("X：%f  Y：%f",skeletonNode2->getAnchorPoint().x,skeletonNode2->getAnchorPoint().y);
    
//    CCLOG("宽度：%f  高度：%f",skeletonNode->boundingBox().size.width,skeletonNode->boundingBox().size.height);
//    CCLOG("X：%f  Y：%f",skeletonNode->boundingBox().origin.x,skeletonNode->boundingBox().origin.y);
//    CCLOG("X：%f  Y：%f",skeletonNode->getPosition().x,skeletonNode->getPosition().y);
}

int GameMianScene::getRand(int start,int end)
{
    cc_timeval psv;
    CCTime::gettimeofdayCocos2d( &psv, NULL );    // 获取本地时间
    //根据时间产生随机种子
    //(这里加上一个rand函数，可解决在循环内(时间间隔极短)取随机数时，
    //连续取得的几个值相同的问题)
    unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
    srand(tsrans);    //设定随机数种子
    float i = CCRANDOM_0_1()*(end-start+1)+start;  //产生一个从start到end间的随机数
    return (int)i;
}

void GameMianScene::startGame(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCTransitionMoveInB* transition = CCTransitionMoveInB ::create(0.5f,HelloWorld::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}
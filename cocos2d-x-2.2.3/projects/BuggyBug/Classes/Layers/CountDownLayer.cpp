//
//  CountDownLayer.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-4-28.
//
//

#include "CountDownLayer.h"
#include "AllDefines.h"
CountDownLayer* CountDownLayer::create( CCCallFuncN *callback )
{
    CountDownLayer *countDownLayer = CountDownLayer::create();
	countDownLayer->initCallback(callback);
	return countDownLayer;
}

bool CountDownLayer::initCallback( CCCallFuncN *callback )
{
	setAllFinishCallback(callback);
	return true;
}

void CountDownLayer::setAllFinishCallback( CCCallFuncN *callback )
{
	if( m_allFinishCallback != callback)
	{
		CC_SAFE_RELEASE( m_allFinishCallback);
		m_allFinishCallback = callback;
		CC_SAFE_RETAIN( m_allFinishCallback);
		m_allFinishCallback->setTarget(this);
	}
}

void CountDownLayer::onEnterTransitionDidFinish()
{
    CCLOG("开始倒计时");
    schedule(schedule_selector(CountDownLayer::startCountDown),1.0);
}

bool CountDownLayer::init()
{
    this->onEnter();

    showTime = 4;
    
	return true;
}

void CountDownLayer::onEnter()
{
    CCNode::onEnter();
}

void CountDownLayer::startCountDown(){
//    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
//    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
//    
//    CCLabelTTF* pLabel1 = CCLabelTTF::create(CCString::createWithFormat("%d",showTime)->getCString(), "Arial", 660);
//    pLabel1->setContentSize(CCSize(568, 320));
//    pLabel1->setPosition(ccp(origin.x + visibleSize.width/2,
//                             origin.y + visibleSize.height - pLabel1->getContentSize().height-50));
//    // add the label as a child to this layer
//    this->addChild(pLabel1, 1);
//    showTime = showTime-1;
//    if (showTime == 0) {
//        pLabel1->setFontSize(120);
//        pLabel1->setString("开始");
//        this->unschedule(schedule_selector(CountDownLayer::startCountDown));
//        CCFiniteTimeAction *actionTwo = CCSequence::create(
//                                                           CCFadeTo::create(1.0f,0.0f),
//                                                           CCCallFuncN::create(this,callfuncN_selector(CountDownLayer::countDownEndCallBack)),
//                                                           NULL
//                                                           );
//        pLabel1->runAction(actionTwo);
//        
//    }else if(showTime > 0){
//        pLabel1->setString(CCString::createWithFormat("%d",showTime)->getCString());
//        CCFiniteTimeAction *actionOne = CCSequence::create(
//                                                           CCScaleTo::create(0.8f,0.0f),
//                                                           NULL
//                                                           );
//        pLabel1->runAction(CCSpawn::create(actionOne,CCFadeTo::create(0.8f,0.0f),NULL));
//    }
    
    CCSprite *numSp = CCSprite::create("num_one.png");
    numSp->setPosition(ccp(CCScreenWidth/2, CCScreenHeight/2));
    numSp->setScale(2);
    this->addChild(numSp);
    
    showTime = showTime-1;
    switch (showTime) {
        case 3:
        {
            CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("num_three.png");
            numSp->setTexture(texture);
        }
            break;
        case 2:
        {
            CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("num_two.png");
            numSp->setTexture(texture);
        }
            break;
        case 1:
        {
            CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("num_one.png");
            numSp->setTexture(texture);
        }
            break;
        case 0:
        {
            this->unschedule(schedule_selector(CountDownLayer::startCountDown));
            this->countDownEndCallBack(numSp);
        }
            break;
        default:
            break;
    }
    
    CCFiniteTimeAction *actionTwo = CCSequence::create(
                                                       CCScaleTo::create(0.5f,0.4f),
                                                       CCDelayTime::create(0.5f),
                                                       CCCallFuncN::create(this,callfuncN_selector(CountDownLayer::countDownEndCallBack)),
                                                       NULL
                                                       );
    numSp->runAction(actionTwo);
}

void CountDownLayer::countDownEndCallBack(CCObject* pSender)
{
    CCSprite *sp = (CCSprite*)pSender;
    sp->removeFromParent();
    if (showTime==0) {
        if( m_allFinishCallback)
        {
            m_allFinishCallback->execute();
        }
    }
    
}
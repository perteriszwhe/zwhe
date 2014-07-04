//
//  GameOverScene.cpp
//  Seven
//
//  Created by He Zhiwei on 14-4-16.
//
//

#include "GameOverScene.h"

CCScene *GameOverScene::scene() {
    
    CCScene* mScene = CCScene::create();
    
    GameOverScene* mLayer = create();
    
    mScene->addChild(mLayer);
    
    return mScene;
}

bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 0)) )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //pLabel = CCLabelTTF::create(numStr.c_str(), "Arial", 50);
    pLabel = CCLabelTTF::create(CCString::createWithFormat("%d",numOne)->getCString(), "Arial", 50);
    
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    scheduleOnce(schedule_selector(GameOverScene::myupdate),0.1);
    
    return true;
}

void GameOverScene::myupdate(){
    CCLOG("点击了！！！！%s",numStr.c_str());
    pLabel->setString(CCString::createWithFormat("%d",numOne)->getCString());
}
#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback1));
    
	pCloseItem->setPosition(ccp(visibleSize.width - (visibleSize.width/2)/2 ,
                                visibleSize.height/2-(visibleSize.height/2)/2));
    
    CCMenuItemImage *pCloseItem2 = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback2));
    
	pCloseItem2->setPosition(ccp((visibleSize.width/2)/2 ,
                                visibleSize.height/2-(visibleSize.height/2)/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, pCloseItem2,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    pLabel = CCLabelTTF::create(CCString::createWithFormat("%d",showTime)->getCString(), "Arial", 50);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
//    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(pSprite, 0);
    
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    // position the sprite on the center of the screen
    CCSize winSizeInPixels = CCDirector::sharedDirector()->getWinSizeInPixels();
    float scaleX = winSizeInPixels.width/1136; //400是实际图片的宽
    pSprite->setScaleX(scaleX);//实际上就是把m_pRoadSprite的宽度设置为OpenGLView的宽度，但是直接用SetContentSize好像不起作用
    
    //pSprite->setContentSize(CCSize(visibleSize.width, visibleSize.height));
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

void HelloWorld::menuCloseCallback1(CCObject* pSender)
{
    if (std::atoi(pLabel->getString())%7==0 || strstr(pLabel->getString(), "7")!=0) {
        CCLOG("错了！！！");
        
        CCScene* scene = CCScene::create();
        GameOverScene *layer = GameOverScene::create();
        layer->numOne = std::atoi(pLabel->getString());
        layer->numStr = "传递的参数bbb";
        scene->addChild(layer);//类似firstScene中的scene()方法
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,scene));
        
//        CCTransitionCrossFade* transition = CCTransitionCrossFade ::create(0.5f,GameOverScene::scene());
//        CCDirector::sharedDirector()->replaceScene(transition);
        
    }else{
        showTime = showTime+1;
        pLabel->setString(CCString::createWithFormat("%d",showTime)->getCString());
    }
}

void HelloWorld::menuCloseCallback2(CCObject* pSender)
{
    if (std::atoi(pLabel->getString())%7==0 || strstr(pLabel->getString(), "7")!=0) {
        showTime = showTime+1;
        pLabel->setString(CCString::createWithFormat("%d",showTime)->getCString());
    }else{
        CCLOG("错了！！！");
        CCScene* scene = CCScene::create();
        GameOverScene *layer = GameOverScene::create();
        layer->numOne = std::atoi(pLabel->getString());
        layer->numStr = "传递的参数aaa";
        scene->addChild(layer);//类似firstScene中的scene()方法
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f,scene));
//        CCTransitionCrossFade* transition = CCTransitionCrossFade ::create(0.5f,GameOverScene::scene());
//        CCDirector::sharedDirector()->replaceScene(transition);
    }
}

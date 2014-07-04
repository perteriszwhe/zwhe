#include "HelloWorldScene.h"
#include "MyNode.h"
#include "SimpleAudioEngine.h"
#include "ScoresManager.h"

static int antNum = ScoresManager::getInstance().antNum;
static int sAntNum = ScoresManager::getInstance().sAntNum;
static float gameTime = ScoresManager::getInstance().gameTime;


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
    this->setTouchEnabled(true);
    isOver = false;
    
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
                                                          menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    //this->addChild(pMenu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    //pLabel = CCLabelTTF::create("3", "Arial", 100);
    
    // position the label on the center of the screen
    //pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
    //origin.y + visibleSize.height - pLabel->getContentSize().height));
    // add the label as a child to this layer
    //this->addChild(pLabel, 1);
    
    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("background.png");
    // position the sprite on the center of the screen
    CCSize winSizeInPixels = CCDirector::sharedDirector()->getWinSizeInPixels();
    float scaleX = winSizeInPixels.width/1136; //400是实际图片的宽
    pSprite->setScaleX(scaleX);//实际上就是把m_pRoadSprite的宽度设置为OpenGLView的宽度，但是直接用SetContentSize好像不起作用
    
    //pSprite->setContentSize(CCSize(visibleSize.width, visibleSize.height));
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    CCSprite* blanket = CCSprite::create("blanket.png");
    blanket->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(blanket, 0);
    
    const char * cakeArra[3];
    cakeArra[0] = "icecream_100.png";
    cakeArra[1] = "cake_100.png";
    cakeArra[2] = "watermelon_100.png";

    CCSprite* cake = CCSprite::create(cakeArra[getRand(0, 2)]);
    cake->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + visibleSize.height/12));
    this->addChild(cake, 0);
    
    cakeFenshuLabel = CCLabelTTF::create("sweet HP：10", "Arial", 26);
    cakeFenshuLabel->setPosition(ccp(100,visibleSize.height-50));
    this->addChild(cakeFenshuLabel, 1);
    
    myFenshuLabel = CCLabelTTF::create("score：0", "Arial", 26);
    myFenshuLabel->setPosition(ccp(visibleSize.width-100,visibleSize.height-50));
    this->addChild(myFenshuLabel, 1);
    
    boCiLabel = CCLabelTTF::create(CCString::createWithFormat("第%d波",ScoresManager::getInstance().boCi)->getCString(), "Arial", 26);
    boCiLabel->setPosition(ccp(visibleSize.width-visibleSize.width/2,visibleSize.height-50));
    this->addChild(boCiLabel, 1);
    
    m_pauseDialog = (PauseDialog *)PauseDialog::layer(this);
    m_pauseDialog->setVisible(false);
    this->addChild(m_pauseDialog , 200);
    
//    CCLayerColor *cakeLayer = CCLayerColor::create(ccc4(255, 255, 255, 255), 90, 70);
//    cakeLayer->setPosition(ccp(visibleSize.width/2-57, visibleSize.height/2+10));
//    this->addChild(cakeLayer);
    

//    CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("rw.plist");
//    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("rw.plist");
    
    ScoresManager::getInstance().selectBoci(ScoresManager::getInstance().boCi);
    antNum = ScoresManager::getInstance().antNum;
    sAntNum = ScoresManager::getInstance().sAntNum;
    gameTime = ScoresManager::getInstance().gameTime;
    schedule(schedule_selector(HelloWorld::myupdate3),2.0);
    
    showTime = 4;
    //atlas = Atlas_readAtlasFile("stronger-ant.atlas");
    
    ////CCParticleExplosion特效
//    CCParticleSystem * p1=CCParticleFire::create();
//    p1->setPosition(ccp((visibleSize.width/2)/2, visibleSize.height/2));
//    p1->setPosVar(ccp(10, 20));
//    p1->setLife(1);
//    p1->setStartSize(35);
//    p1->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
//    p1->setAutoRemoveOnFinish(true);
//    this->addChild(p1,100);
//    
//    CCParticleSystem * p2=CCParticleFire::create();
//    p2->setPosition(ccp(visibleSize.width/2, visibleSize.height/2-((visibleSize.height/2)/2)));
//    p2->setPosVar(ccp(20, 20));
//    p2->setLife(1);
//    p2->setStartSize(35);
//    p2->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
//    p2->setAutoRemoveOnFinish(true);
//    this->addChild(p2,100);
//    
//    CCParticleSystem * p3=CCParticleFire::create();
//    p3->setPosition(ccp((visibleSize.width/2)/2+visibleSize.width/2, visibleSize.height/2));
//    p3->setPosVar(ccp(20, 20));
//    p3->setLife(1);
//    p2->setStartSize(35);
//    p3->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
//    p3->setAutoRemoveOnFinish(true);
//    this->addChild(p3,100);
//    
//    CCParticleSystem * p4=CCParticleFire::create();
//    p4->setPosition(ccp(visibleSize.width/2, visibleSize.height/2+((visibleSize.height/2)/2)));
//    p4->setPosVar(ccp(20, 20));
//    p4->setLife(1);
//    p4->setStartSize(35);
//    p4->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
//    p4->setAutoRemoveOnFinish(true);
//    this->addChild(p4,100);
    
//    cc_timeval tv;
//    CCTime::gettimeofdayCocos2d(&tv,NULL);
//    //都转化为毫秒
//    unsigned long reed = tv.tv_sec*1000+tv.tv_usec/1000;
//    //srand()中传入一个随机数种子
//    srand(reed);
    return true;
}

void HelloWorld::myupdate(float dt){
    //CCLOG("%f",dt);
    if (gameTime>0.0f && antNum>0) {
        CCSize mysize=CCDirector::sharedDirector()->getWinSize();
        //_fasterAnt = (NormalFasterAnt*)NormalFasterAnt::createWithFile("stronger-ant.json", atlas);
        _normalAnt = (NormalAnt*)NormalAnt::createWithFile("basic-ant.json", "basic-ant.atlas");
        //_normalAnt->setMix("walk", "run & cry", 0.4f);
        //CCLOG("宽度：%f",_fasterAnt);
        CCLOG("高度：%f",_normalAnt->boundingBox().size.height);
        CCPoint pointArr[4];
        pointArr[0] = ccp(0-20,getRand(0, mysize.height));
        pointArr[1] = ccp(mysize.width+20,getRand(0, mysize.height));
        pointArr[2] = ccp(getRand(0, mysize.width),0-50);
        pointArr[3] = ccp(getRand(0, mysize.width),mysize.height);
        _normalAnt->setPosition(pointArr[getRand(0, 3)]);
        _normalAnt->startPoint = _normalAnt->getPosition();
        this->addChild(_normalAnt,0);
        antNum = antNum-1;
        
        //CCLOG("平均时间：%f",gameTime/antNum);
        this->unschedule(schedule_selector(HelloWorld::myupdate));
        //float currTime = this->myRand_0_1(0.0,gameTime/antNum);
        float currTime = gameTime/antNum;
    
        if (gameTime-currTime<=0) {
            gameTime = gameTime-0.1f;
            schedule(schedule_selector(HelloWorld::myupdate),0.1f);
        }else{
            gameTime = gameTime-currTime;
            schedule(schedule_selector(HelloWorld::myupdate),currTime);
        }
        
    }else{
        //CCLOG("剩余：%f秒",gameTime);
        bool isBociOver = true;
        CCObject *temp;
        CCArray *nodeArray = this->getChildren();
        CCARRAY_FOREACH(nodeArray, temp)
        {
            bool s1IsDestHole = dynamic_cast<NormalAnt*>(temp) != NULL;
            if(s1IsDestHole){
                isBociOver = false;
            }
        }
        
        if (isBociOver) {
            this->unschedule(schedule_selector(HelloWorld::myupdate));
            
            schedule(schedule_selector(HelloWorld::myupdate3),1.0);
            ScoresManager::getInstance().boCi = ScoresManager::getInstance().boCi+1;
            ScoresManager::getInstance().selectBoci(ScoresManager::getInstance().boCi);
            boCiLabel->setString(CCString::createWithFormat("第%d波",ScoresManager::getInstance().boCi)->getCString());
            
            antNum = ScoresManager::getInstance().antNum;
            sAntNum = ScoresManager::getInstance().sAntNum;
            gameTime = ScoresManager::getInstance().gameTime;
        }
    }
    //this->unschedule(schedule_selector(HelloWorld::myupdate));
}

void HelloWorld::myupdate2(float dt){
    //CCLOG("%f",dt);
    if (gameTime>0.0f && sAntNum>0) {
        CCSize mysize=CCDirector::sharedDirector()->getWinSize();
        _normalAnt = (NormalAnt*)NormalAnt::createWithFile("stronger-and-faster-ant.json", "stronger-and-faster-ant.atlas");
        //_normalAnt->setMix("walk", "run & cry", 0.4f);
        
        CCPoint pointArr[4];
        pointArr[0] = ccp(0-20,getRand(0, mysize.height));
        pointArr[1] = ccp(mysize.width+20,getRand(0, mysize.height));
        pointArr[2] = ccp(getRand(0, mysize.width),0-50);
        pointArr[3] = ccp(getRand(0, mysize.width),mysize.height);
        _normalAnt->setPosition(pointArr[getRand(0, 3)]);
        _normalAnt->startPoint = _normalAnt->getPosition();
        //_normalAnt->setScale(1);
        this->addChild(_normalAnt,0);
        sAntNum = sAntNum-1;
        
        CCLOG("平均时间：%f",gameTime/sAntNum);
        this->unschedule(schedule_selector(HelloWorld::myupdate2));
        //float currTime = this->myRand_0_1(0.0,gameTime/antNum);
        float currTime = gameTime/sAntNum;
        
        if (gameTime-currTime<=0) {
            gameTime = gameTime-0.1f;
            schedule(schedule_selector(HelloWorld::myupdate2),0.1f);
        }else{
            gameTime = gameTime-currTime;
            schedule(schedule_selector(HelloWorld::myupdate2),currTime);
        }
        
    }else{
        CCLOG("剩余：%f秒",gameTime);
        this->unschedule(schedule_selector(HelloWorld::myupdate2));
    }
}

void HelloWorld::myupdate3(){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCLabelTTF* pLabel1 = CCLabelTTF::create(CCString::createWithFormat("%d",showTime)->getCString(), "Arial", 660);
    pLabel1->setContentSize(CCSize(568, 320));
    pLabel1->setPosition(ccp(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - pLabel1->getContentSize().height-50));
    // add the label as a child to this layer
    this->addChild(pLabel1, 1);
    showTime = showTime-1;
    if (showTime == 0) {
        pLabel1->setFontSize(120);
        pLabel1->setString(CCString::createWithFormat("第%d波开始",ScoresManager::getInstance().boCi)->getCString());
        this->unschedule(schedule_selector(HelloWorld::myupdate3));
        //schedule(schedule_selector(HelloWorld::myupdate2),1.0);
        //scheduleOnce(schedule_selector(HelloWorld::menuSetVisableFalse),1.0)
        //scheduleOnce(schedule_selector(HelloWorld::menuSetVisableFalse2), 3);
    
        CCFiniteTimeAction *actionTwo = CCSequence::create(
                                                           CCFadeTo::create(1.0f,0.0f),
                                                           CCCallFuncN::create(this,callfuncN_selector(HelloWorld::menuSetVisableFalse2)),
                                                           NULL
                                                           );
        pLabel1->runAction(actionTwo);
        
    }else if(showTime > 0){
        pLabel1->setString(CCString::createWithFormat("%d",showTime)->getCString());
        CCFiniteTimeAction *actionOne = CCSequence::create(
                                                           CCScaleTo::create(0.8f,0.0f),
                                                           CCCallFuncN::create(this,callfuncN_selector(HelloWorld::menuSetVisableFalse)),
                                                           NULL
                                                           );
        pLabel1->runAction(CCSpawn::create(actionOne,CCFadeTo::create(0.8f,0.0f),NULL));
        this->unschedule(schedule_selector(HelloWorld::myupdate3));
        schedule(schedule_selector(HelloWorld::myupdate3),1.0);
    }
    
}

void HelloWorld::CallFucnCallback1(CCObject* pSender)
{
    CCSprite* sp3 = (CCSprite*)pSender;
    sp3->removeFromParent();
}

void HelloWorld::menuSetVisableFalse(CCObject* pSender)
{
    CCLabelTTF* labelStr = (CCLabelTTF*)pSender;
    labelStr->removeFromParent();
}

void HelloWorld::menuSetVisableFalse2(CCObject* pSender)
{
    showTime = 4;
    CCLabelTTF* labelStr = (CCLabelTTF*)pSender;
    labelStr->removeFromParent();
    if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gamebg2.mp3", true);
    }
    
    schedule(schedule_selector(HelloWorld::myupdate),gameTime/antNum);
    gameTime = gameTime-gameTime/antNum;
    
    if (gameTime>0.0f && sAntNum>0){
        schedule(schedule_selector(HelloWorld::myupdate2),gameTime/sAntNum);
    }
    //gameTime = gameTime-gameTime/sAntNum;
    
}

int HelloWorld::getRand(int start,int end)
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

float HelloWorld::myRand_0_1(float start,float end)
{
    cc_timeval psv;
    CCTime::gettimeofdayCocos2d( &psv, NULL );    // 获取本地时间
    //根据时间产生随机种子
    //(这里加上一个rand函数，可解决在循环内(时间间隔极短)取随机数时，
    //连续取得的几个值相同的问题)
    unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
    srand(tsrans);    //设定随机数种子
    return CCRANDOM_0_1()*(end-start+0.1)+start;
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


//void HelloWorld::onEnter()
//{
//    CCLayer::onEnter();
//    CCDirector* pDirector = CCDirector::sharedDirector();
//    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
//}
//
//void HelloWorld::onExit()
//{
//    CCLayer::onExit();
//    CCDirector* pDirector = CCDirector::sharedDirector();
//    pDirector->getTouchDispatcher()->removeDelegate(this);
//    
//}
//
//bool HelloWorld::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
//{
//	return true;
//}
//
//void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
//{
//    CCObject *temp;
//    //获得rootnode根下的节点
//    CCArray *nodeArray = this->getChildren();
//    CCLOG("%d",nodeArray->count());
//    CCARRAY_FOREACH(nodeArray, temp)
//    {
//        //NormalAnt* currAnt = (NormalAnt*)temp;
//        bool s1IsDestHole = dynamic_cast<NormalAnt*>(temp) != NULL;
//        //判断rootnode的节点下还是否存在节点 遍历调用
//        if(s1IsDestHole){
//            NormalAnt* currAnt = (NormalAnt*)temp;
//            CCLOG("触发了！！！");
//            if (isTouchMe(pTouch, currAnt) && currAnt->roleState == kRoleStateWalk) {
//                CCLOG("点击了！！！！");
//                CCParticleSystem * p1=CCParticleFire::create();
//                p1->setPosition(0, 50);
//                p1->setPosVar(ccp(10, 20));
//                p1->setLife(1);
//                p1->setStartSize(35);
//                p1->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
//                p1->setAutoRemoveOnFinish(false);
//                currAnt->addChild(p1,100);
//                currAnt->setState(kRoleStateIdle);
//                currAnt->changeDirection();
//                currAnt->setAnimation("run & cry", true,0);
//                currAnt->stopAllActions();
//                
//                currAnt->endMove(currAnt->startPoint,ccpDistance(currAnt->getPosition(),currAnt->startPoint)/130);
//            }
//        }else{
//            CCLOG("没有触发！！！");
//        }
//        //这里 do something
//    }
//}
//
////5, 10, 10-n-r, 10-s-r
//void HelloWorld::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent ){
//    
//}
//
//bool HelloWorld::isTouchMe( CCTouch* pTouch,NormalAnt* ant )
//{
//    //获得点击的OpenGL的世界坐标值
//    CCPoint touchPoint = pTouch->getLocation();
//    //将点击的位置转换成父元素坐标系中的相对坐标
//    CCPoint pt=ant->getParent()->convertToNodeSpace(touchPoint);
//    CCLOG("点击的坐标X：%f  Y:%f",pt.x,pt.y);
//    //得到自己在父元素坐标系中的位置范围
//    CCRect rect=ant->boundingBox();
//    CCLOG("自己的坐标X：%f  Y:%f",rect.origin.x,rect.origin.y);
//    //判断是否点击落在自己的范围当中， 以上判断全是在父元素坐标系中进行计算
//    //rect.containsPoint(pt);
//    //42.4  65.5
//    if(pt.x >= rect.origin.x && pt.x <= rect.origin.x+rect.size.width
//       && pt.y >= rect.origin.y && pt.y <= rect.origin.y+rect.size.height)
//    {
//        return true;
//    }
//    return false;
//}

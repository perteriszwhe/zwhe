//
//  GameMianScene.cpp
//  TestCocos2dx
//
//  Created by He Zhiwei on 14-4-25.
//
//

#include "GameMianScene.h"
#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
#include "StoreScene.h"
static float liziShowTime = 0.0f;
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
    
    this->setBackground("");
    
    CCLabelTTF *logLabel = CCLabelTTF::create("Buggy Bug", "AmericanTypewriter-Bold", 60);
    logLabel->setPosition(ccp(windowSize.width-windowSize.width/2,windowSize.height-70));
    this->addChild(logLabel, 1);
    
    CCMenuItemFont::setFontSize(50);
    CCMenuItemFont * playBut = CCMenuItemFont::create("PLAY" , this, menu_selector(GameMianScene::startGame));
    CCMenuItemFont::setFontSize(50);
    CCMenuItemFont * storeBut = CCMenuItemFont::create("STORE" , this, menu_selector(GameMianScene::gotoStore));
    CCMenuItemFont::setFontSize(50);
	CCMenu * menu = CCMenu::create(playBut , storeBut , NULL);
    menu->alignItemsVertically();
	menu->setPosition(ccp(windowSize.width-windowSize.width/2,windowSize.height/2-200));
	menu->setTag(200);
	this->addChild(menu);
    
    liziShowTime = 10;
    //下雨效果
    xiayu = CCParticleRain::create();
    xiayu->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
    xiayu->setSpeed(630);
    xiayu->setSpeedVar(130);
    xiayu->setStartSize(6.0f);
    xiayu->setStartSizeVar(2.0f);
    xiayu->setEndSize(kCCParticleStartSizeEqualToEndSize);
    xiayu->setEmissionRate(100);
    //xiayu->setAutoRemoveOnFinish(true);                          // 完成后制动移除
    xiayu->setDuration(liziShowTime);
    addChild(xiayu);
    xiayu->stopSystem();

    //下雪效果
    xiaxue = CCParticleSnow::create();
    xiaxue->setTexture(CCTextureCache::sharedTextureCache()->addImage("snow.png"));
    xiaxue->setSpeed(150);
    xiaxue->setSpeedVar(30);
    xiaxue->setDuration(liziShowTime);
    addChild(xiaxue);
    xiaxue->stopSystem();
    
    //太阳效果
    taiyang = CCParticleSun::create();
    taiyang->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
    taiyang->setStartSize(200.0f);
    taiyang->setStartSizeVar(2.0f);
    taiyang->setEmissionRate(30);
    taiyang->setPosition(ccp(200,-20));
    addChild(taiyang);
    taiyang->stopSystem();
//    moveTo=CCMoveTo::create(2.0f,ccp(200,CCScreenHeight/2+200));
//    moveTo2=CCMoveTo::create(2.0f,ccp(0,0));
    
    yezi = CCParticleSystemQuad::create("shuye.plist");
    yezi->setPosition(ccp(CCScreenWidth, CCScreenHeight));
    yezi->setPosVar(ccp(CCScreenWidth, 0));
    yezi->setStartSize(50.0f);
    yezi->setEndSize(50.0f);                         // 完成后制动移除
    yezi->setDuration(liziShowTime);
    addChild(yezi,10);
    yezi->stopSystem();
    
    schedule(schedule_selector(GameMianScene::addAnt),1);
    schedule(schedule_selector(GameMianScene::myupdate),1,1000,1);
    
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("homebg2.mp3", true);
    
    
    
//    CCSpriteFrameCache *frameCache=CCSpriteFrameCache::sharedSpriteFrameCache();
//    frameCache->addSpriteFramesWithFile("feng.plist");
//    
//    CCAnimationCache *animationCache =CCAnimationCache::sharedAnimationCache();
//    animationCache->addAnimationsWithFile("feng.plist");
//    CCAnimation* animation = animationCache->animationByName("frames");
//    
//    CCAnimate* animate = CCAnimate::create(animation);
//    CCSprite* grossini = CCSprite::create();
//    CCSpriteFrame* frame = frameCache->spriteFrameByName("精选技能光效 (7)0001.png");
//    grossini->setDisplayFrame(frame);
    
    return true;
}

void GameMianScene::setBackground( const char *img )
{
    //	m_bgSprite = CCSprite::create(img);
    //	m_bgSprite->setAnchorPoint(ccp(0,0));
    //	m_bgSprite->setPosition(ccp(100,100));
    //	this->addChild(m_bgSprite,-1);
    CCSize winSizeInPixels = CCDirector::sharedDirector()->getWinSizeInPixels();
    float scaleX = winSizeInPixels.width/650; //400是实际图片的宽
    float scaleY = winSizeInPixels.height/398;
    
    m_bgSprite01 = CCSprite::create("taiyangbg.png");
    m_bgSprite01->setScaleX(scaleX);//实际上就是把m_pRoadSprite的宽度设置为OpenGLView的宽度，但是直接用SetContentSize好像不起作用
    m_bgSprite01->setScaleY(scaleY);
    m_bgSprite01->setPosition(ccp(CCScreenWidth/2, CCScreenHeight*2));
    this->addChild(m_bgSprite01,-1);
    
    m_bgSprite02 = CCSprite::create("xiayubg.png");
    m_bgSprite02->setScaleX(scaleX);//实际上就是把m_pRoadSprite的宽度设置为OpenGLView的宽度，但是直接用SetContentSize好像不起作用
    m_bgSprite02->setScaleY(scaleY);
    m_bgSprite02->setPosition(ccp(CCScreenWidth/2, CCScreenHeight*2));
    this->addChild(m_bgSprite02,-1);
    
    m_bgSprite03 = CCSprite::create("yezibg.png");
    m_bgSprite03->setScaleX(scaleX);//实际上就是把m_pRoadSprite的宽度设置为OpenGLView的宽度，但是直接用SetContentSize好像不起作用
    m_bgSprite03->setScaleY(scaleY);
    m_bgSprite03->setPosition(ccp(CCScreenWidth/2, CCScreenHeight*2));
    this->addChild(m_bgSprite03,-1);
    
    m_bgSprite04 = CCSprite::create("xiaxuebg.png");
    m_bgSprite04->setScaleX(scaleX);//实际上就是把m_pRoadSprite的宽度设置为OpenGLView的宽度，但是直接用SetContentSize好像不起作用
    m_bgSprite04->setScaleY(scaleY);
    m_bgSprite04->setPosition(ccp(CCScreenWidth/2, CCScreenHeight*2));
    this->addChild(m_bgSprite04,-1);
}

void GameMianScene::addAnt(){
    CCSize windowSize = CCDirector::sharedDirector()->getWinSize();
    
    AntType antArra[4];
    antArra[0] = tBasicAnt;
    antArra[1] = tFasterAnt;
    antArra[2] = tStrongerFasterAnt;
    antArra[3] = tStrongerAnt;
    
    const char * poseArra[5];
    poseArra[0] = "run & cry";
    poseArra[1] = "walk";
    poseArra[2] = "carrying pose 1";
    poseArra[3] = "carrying pose 2";
    poseArra[4] = "carrying pose 3";
    int i = getRand(0, 3);
    int b = getRand(0, 4);
    CCSkeletonAnimation * skeletonNode4 = CCSkeletonAnimation::createWithData(ScoresManager::getInstance().getSpineData(antArra[i]));
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
    if (!xiaxue->isActive() && !xiayu->isActive() && !yezi->isActive() && !taiyang->isActive()) {
        m_bgSprite01->runAction(CCMoveTo::create(0.5, ccp(CCScreenWidth/2, CCScreenHeight/2)));
        taiyang->resetSystem();
        taiyang->runAction(CCMoveTo::create(0.5f,ccp(200,CCScreenHeight/2+200)));
    }else if(taiyang->isActive()){
        //CCCallFuncN* callBackLizi=CCCallFuncN::create(this, callfuncN_selector(GameMianScene::taiyangHideCallBack));
        CCArray* actionArray=CCArray::create();
        actionArray->addObject(CCMoveTo::create(0.5f,ccp(200,-20)));
        //actionArray->addObject(callBackLizi);
        CCSequence* sequeneAction=CCSequence::create(actionArray);
        taiyang->runAction(sequeneAction);
        taiyang->stopSystem();
        xiayu->resetSystem();
        m_bgSprite02->runAction(CCMoveTo::create(0.5, ccp(CCScreenWidth/2, CCScreenHeight/2)));
        m_bgSprite01->runAction(CCMoveTo::create(0.5, ccp(CCScreenWidth/2, -CCScreenHeight/2)));
        m_bgSprite04->setPosition(ccp(CCScreenWidth/2, CCScreenHeight*2));
    }else if(xiayu->isActive()){
        xiayu->stopSystem();
        yezi->resetSystem();
        m_bgSprite03->runAction(CCMoveTo::create(0.5, ccp(CCScreenWidth/2, CCScreenHeight/2)));
        m_bgSprite02->runAction(CCMoveTo::create(0.5, ccp(CCScreenWidth/2, -CCScreenHeight/2)));
        m_bgSprite01->setPosition(ccp(CCScreenWidth/2, CCScreenHeight*2));
    }else if(yezi->isActive()){
        yezi->stopSystem();
        xiaxue->resetSystem();
        m_bgSprite04->runAction(CCMoveTo::create(0.5, ccp(CCScreenWidth/2, CCScreenHeight/2)));
        m_bgSprite03->runAction(CCMoveTo::create(0.5, ccp(CCScreenWidth/2, -CCScreenHeight/2)));
        m_bgSprite02->setPosition(ccp(CCScreenWidth/2, CCScreenHeight*2));
    }else if(xiaxue->isActive()){
        xiaxue->stopSystem();
        taiyang->resetSystem();
        taiyang->runAction(CCMoveTo::create(0.5f,ccp(200,CCScreenHeight/2+200)));
        m_bgSprite01->runAction(CCMoveTo::create(0.5, ccp(CCScreenWidth/2, CCScreenHeight/2)));
        m_bgSprite04->runAction(CCMoveTo::create(0.5, ccp(CCScreenWidth/2, -CCScreenHeight/2)));
        m_bgSprite03->setPosition(ccp(CCScreenWidth/2, CCScreenHeight*2));
//        CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("data6.bin_0.png");
//        m_bgSprite->setTexture(texture);
    }
    schedule(schedule_selector(GameMianScene::myupdate),liziShowTime-1);
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
    CCTransitionMoveInB* transition = CCTransitionMoveInB ::create(0.5f,GamePlayScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}

void GameMianScene::gotoStore(){
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCTransitionMoveInB* transition = CCTransitionMoveInB ::create(0.5f,StoreScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}

//void GameMianScene::taiyangHideCallBack(){
//    taiyang->stopSystem();
//    xiayu->resetSystem();
//}
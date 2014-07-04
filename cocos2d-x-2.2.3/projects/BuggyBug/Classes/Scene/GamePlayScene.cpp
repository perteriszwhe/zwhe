//
//  GamePlayScene.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-4-27.
//
//

#include "GamePlayScene.h"
#include "UITools.h"
#include "UILoaderAchieve.h"
#include "UILoaderTroop.h"
#include "UILoaderAnt.h"
#include "ConfigCache.h"
#include "ScoresManager.h"
#include "SimpleAudioEngine.h"
#include "UILoaderLevel.h"

PropertyStruct troopProperty;

//static int antNum = ScoresManager::getInstance().antNum;
//static int sAntNum = ScoresManager::getInstance().sAntNum;
//static float gameTime = ScoresManager::getInstance().gameTime;

static float gameTime;
static int antNumCount;
static int levelNumber;

CCScene* GamePlayScene::scene()
{
    CCScene *scene = CCScene::create();
    GamePlayScene *layer = GamePlayScene::create();
    scene->addChild(layer);
    return scene;
}

GamePlayScene::GamePlayScene(void)
{
}


GamePlayScene::~GamePlayScene(void)
{
}

bool GamePlayScene::init()
{
    if( !CCLayer::init()) return false;
    this->setBackground("background2.png");
    //this->setPicnicCloth("blanket.png");
    this->setSweetSprite();
    this->setOther();
    this->setPlayLayer();
    
    UILoaderAchieve *loader = UILoaderAchieve::create("achieve.xml");
    AchieveStruct achieve = loader->getAchieve(1);
    CCLOG("%s",achieve.key);
    
//    UILoaderTroop *troop = (UILoaderTroop*)ConfigCache::sharedConfigCache()->getConfig(xml_type_troop);
//	RoleStruct role = troop->getRole(1);
//    CCLOG("%s",role.name.c_str());
    
    UILoaderAnt *antLoader = (UILoaderAnt*)ConfigCache::sharedConfigCache()->getConfig(xml_type_ant);
    AntStruct ant = antLoader->getRole(1);
    CCLOG("%s",ant.name.c_str());
    
    return true;
}

void GamePlayScene::setBackground( const char *img )
{
//	m_bgSprite = CCSprite::create(img);
//	m_bgSprite->setAnchorPoint(ccp(0,0));
//	m_bgSprite->setPosition(ccp(100,100));
//	this->addChild(m_bgSprite,-1);
    
    m_bgSprite = CCSprite::create(img);
//    CCSize winSizeInPixels = CCDirector::sharedDirector()->getWinSizeInPixels();
//    float scaleX = winSizeInPixels.width/650; //400是实际图片的宽
//    float scaleY = winSizeInPixels.height/398;
//    m_bgSprite->setScaleX(scaleX);//实际上就是把m_pRoadSprite的宽度设置为OpenGLView的宽度，但是直接用SetContentSize好像不起作用
//    m_bgSprite->setScaleY(scaleY);
    m_bgSprite->setPosition(ccp(CCScreenWidth/2, CCScreenHeight/2));
    this->addChild(m_bgSprite,-1);
}

void GamePlayScene::setPicnicCloth( const char *img )
{
	CCSprite* blanket = CCSprite::create(img);
    blanket->setPosition(ccp(CCScreenWidth/2, CCScreenHeight/2));
    this->addChild(blanket, 0);
}

void GamePlayScene::setSweetSprite()
{
	CCSprite * sweetSprite = UITools::createSweetByRand();
    sweetSprite->setPosition(ccp(CCScreenWidth/2, CCScreenHeight/2 + CCScreenWidth/30));
    this->addChild(sweetSprite, 0);
}

void GamePlayScene::setOther(){
//    cakeFenshuLabel = CCLabelTTF::create("sweet HP：10", "Arial", 26);
//    cakeFenshuLabel->setPosition(ccp(100,CCScreenHeight-50));
//    this->addChild(cakeFenshuLabel, 1);
//    
//    myFenshuLabel = CCLabelTTF::create("score：0", "Arial", 26);
//    myFenshuLabel->setPosition(ccp(CCScreenWidth-100,CCScreenHeight-50));
//    this->addChild(myFenshuLabel, 1);
    
    //boCiLabel = CCLabelTTF::create(CCString::createWithFormat("第%d波",ScoresManager::getInstance().boCi)->getCString(), "Arial", 26);
    //boCiLabel->setPosition(ccp(CCScreenWidth-CCScreenWidth/2,CCScreenHeight-50));
    //this->addChild(boCiLabel, 1);
    
//    ScoresManager::getInstance().selectBoci(ScoresManager::getInstance().boCi);
//    antNum = ScoresManager::getInstance().antNum;
//    sAntNum = ScoresManager::getInstance().sAntNum;
//    gameTime = ScoresManager::getInstance().gameTime;
    
    downLayer = CountDownLayer::create(CCCallFuncN::create(this,callfuncN_selector(GamePlayScene::countDownEndCallBack)));
    //downLayer->setPosition(ccp(CCScreenWidth/2, CCScreenHeight/2));
    this->addChild(downLayer);
    
    m_pauseDialog = (PauseDialogLayer *)PauseDialogLayer::layer(this);
    m_pauseDialog->setVisible(false);
    this->addChild(m_pauseDialog , 200);
    
    m_pause = (PauseLayer *)PauseLayer::layer(this);
    m_pause->setVisible(false);
    this->addChild(m_pause , 200);
    
    levelNumber = 1;
}

void GamePlayScene::setPlayLayer()
{
    playLayer = PlayLayer::create(NULL, NULL);
    this->addChild(playLayer,100);
}

void GamePlayScene::countDownEndCallBack(CCNode *node)
{
	this->removeChild(downLayer);
    CCLOG("倒计时结束");
    if (!CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gamebg2.mp3", true);
    }
    
    arr = this->loadLevelData(levelNumber);
    arr->retain();
    schedule(schedule_selector(GamePlayScene::showAntUpdate),gameTime/antNumCount);
}

void GamePlayScene::showAntUpdate(){
    ScoresManager::getInstance().boCi = levelNumber;
    playLayer->m_TimeLabel->setString(CCString::createWithFormat("%d",ScoresManager::getInstance().boCi)->getCString());
    ScoresManager::getInstance().selectBoci(ScoresManager::getInstance().boCi);
    
    if (gameTime>0.0f && antNumCount>0) {
        int rand = UITools::getRandForInt(0, arr->count()-1);
        CCLog("随机数：%d",arr->count());
        _normalAnt = (BaseAnt*)arr->objectAtIndex(rand);
        addChild(_normalAnt);
        arr->removeObject(_normalAnt);
        CCLog("还剩蚂蚁：%d",arr->count());
        antNumCount = arr->count();
    }else{
        bool isBociOver = true;
        CCObject *temp;
        CCArray *nodeArray = this->getChildren();
        CCARRAY_FOREACH(nodeArray, temp)
        {
            bool s1IsDestHole = dynamic_cast<BaseAnt*>(temp) != NULL;
            if(s1IsDestHole){
                isBociOver = false;
            }
        }
        if (isBociOver) {
            this->unschedule(schedule_selector(GamePlayScene::showAntUpdate));
            arr->removeAllObjects();
            arr->release();
            
            levelNumber = levelNumber+1;
            arr = this->loadLevelData(levelNumber);
            arr->retain();
            schedule(schedule_selector(GamePlayScene::showAntUpdate),gameTime/antNumCount,1000,3.0f);
        }
    }
}

void GamePlayScene::addOneOfNormalAnt(AntType antType,bool isRand){
    if (!isRand) {
        _normalAnt = (BaseAnt*)BaseAnt::createWithType(antType);
    }else{
        AntType allAntType[] = {tBasicAnt,tFasterAnt,tStrongerFasterAnt};
        int len;
        GET_ARRAY_LEN(allAntType,len);
        _normalAnt = (BaseAnt*)BaseAnt::createWithType(allAntType[UITools::getRandForInt(0, len-1)]);
    }
    _normalAnt->setPosition(UITools::createAntStartPoint());
    _normalAnt->startPoint = _normalAnt->getPosition();
    this->addChild(_normalAnt,0);
}

void GamePlayScene::addOneOfSuperAnt(AntType antType,bool isRand){
    if (!isRand) {
        _normalAnt = (BaseAnt*)BaseAnt::createWithType(antType);
    }else{
        AntType allAntType[] = {tFasterAnt,tStrongerFasterAnt};
        int len;
        GET_ARRAY_LEN(allAntType,len);
        _normalAnt = (BaseAnt*)BaseAnt::createWithType(allAntType[UITools::getRandForInt(0, len-1)]);
    }
    _normalAnt->setPosition(UITools::createAntStartPoint());
    _normalAnt->startPoint = _normalAnt->getPosition();
    this->addChild(_normalAnt,0);
}

CCArray* GamePlayScene::loadLevelData(int levelNum){
    UILoaderLevel *levelLoader = (UILoaderLevel*)ConfigCache::sharedConfigCache()->getConfig(xml_type_level);
    LevelStruct level = levelLoader->getRole(levelNum);
    LevelPropertyIt levelIt;
    CCArray *antArr = CCArray::create();
    for (levelIt = level.attributes.begin(); levelIt != level.attributes.end(); ++levelIt) {
        atoi((levelIt->second.number).c_str());
        for (int i=0; i<atoi((levelIt->second.number).c_str()); i++) {
            BaseAnt *nAnt = (BaseAnt*)BaseAnt::createWithType((AntType)atoi((levelIt->second.ant).c_str()));
            nAnt->setPosition(UITools::createAntStartPoint());
            nAnt->startPoint = nAnt->getPosition();
            antArr->addObject(nAnt);
        }
    }
    gameTime = atoi((level.time).c_str());
    antNumCount = antArr->count();
    return antArr;
}

void GamePlayScene::onEnter()
{
	CCLayer::onEnter();
}

void GamePlayScene::onExit()
{
	CCLayer::onExit();
}
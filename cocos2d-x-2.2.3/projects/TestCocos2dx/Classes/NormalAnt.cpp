//
//  NormalAnt.cpp
//  TestCocos2dx
//
//  Created by He Zhiwei on 14-4-10.
//
//

#include "NormalAnt.h"
#include "ScoresManager.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

static HelloWorld* pNode;
//NormalAnt * NormalAnt::createWithSpriteFrameName(const char *pszSpriteFrameName){
//    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
//    
//#if COCOS2D_DEBUG > 0
//    char msg[256] = {0};
//    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
//    CCAssert(pFrame != NULL, msg);
//#endif
//    
//    return createWithSpriteFrame(pFrame);
//}
//
//NormalAnt* NormalAnt::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
//{
//    NormalAnt *pobSprite = new NormalAnt();
//    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
//    {
//        pobSprite->autorelease();
//        return pobSprite;
//    }
//    CC_SAFE_DELETE(pobSprite);
//    return NULL;
//}

NormalAnt* NormalAnt::createWithFile (const char* skeletonDataFile, Atlas* atlas, float scale) {
	NormalAnt* node = new NormalAnt(skeletonDataFile, atlas, scale);
	node->autorelease();
	return node;
}

NormalAnt::NormalAnt (const char* skeletonDataFile, Atlas* atlas, float scale)
: CCSkeletonAnimation(skeletonDataFile, atlas, scale) {
	addAnimationState();
}

NormalAnt* NormalAnt::createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale) {
	NormalAnt* node = new NormalAnt(skeletonDataFile, atlasFile, scale);
	node->autorelease();
	return node;
}

NormalAnt::NormalAnt (const char* skeletonDataFile, const char* atlasFile, float scale)
: CCSkeletonAnimation(skeletonDataFile, atlasFile, scale) {
	addAnimationState();
}

//NormalAnt::NormalAnt(){
//    arrayActions=CCArray::createWithCapacity(1);
//    arrayActions->retain();
//}

NormalAnt::~NormalAnt(){
    CC_SAFE_RELEASE(arrayActions);
}

void NormalAnt::onEnterTransitionDidFinish(){
    
    pNode = (HelloWorld*)getParent();
    schedule(schedule_selector(NormalAnt::checkBox));
    
    this->initSelf();
    this->initActions();
    
    cc_timeval tv;
    CCTime::gettimeofdayCocos2d(&tv,NULL);
    //都转化为毫秒
    unsigned long reed = tv.tv_sec*1000+tv.tv_usec/1000;
    //srand()中传入一个随机数种子
    srand(reed);
}

void NormalAnt::initActions(){
    //idle
    arrayActions=CCArray::createWithCapacity(1);
    arrayActions->retain();
    
//    CCArray * idleArray=CCArray::createWithCapacity(4);
//    for (int i=1; i<5; i++) {
//        CCString * strFrameName=CCString::createWithFormat("r%d.png",i);
//        CCSpriteFrame * frameIdle=CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strFrameName->getCString());
//        idleArray->addObject(frameIdle);
//    }
//    CCAnimation * animationIdle=CCAnimation::createWithSpriteFrames(idleArray);
//    animationIdle->setDelayPerUnit(0.1);
//    CCAnimate * animateIdle=CCAnimate::create(animationIdle);
//    arrayActions->addObject(CCRepeatForever::create(animateIdle));
    
    CCSize mysize=CCDirector::sharedDirector()->getWinSize();
    if (startPoint.x>mysize.width/2) {
        setDirection(kRoleDirectionLeft);
    }else{
        setDirection(kRoleDirectionRight);
    }
    //this->starAction();
    this->starMove(ccp(mysize.width/2,mysize.height/2),8.0f);
}

void NormalAnt::initSelf(){
    this->totalBlood=600;
    this->speed = 6.0f;
    this->setAnimation("walk", true,0);
    this->setSkin("male");
    //this->debugSlots = true;
    //this->debugBones = true;
    this->setScale(0.5);
    roleState = kRoleStateWalk;
}

void NormalAnt::starAction(){
    //this->stopAllActions();
    //this->runAction((CCAction*)arrayActions->objectAtIndex(0));
    //this->setState(kRoleStateWalk);
}

void NormalAnt::starMove(CCPoint point,float time){
    CCMoveTo* moveTo=CCMoveTo::create(time, point);
    CCCallFuncN* callBackIdle=CCCallFuncN::create(this, callfuncN_selector(NormalAnt::CallFucnCallback1));
    
    CCArray* actionArray=CCArray::create();
    actionArray->addObject(moveTo);
    actionArray->addObject(callBackIdle);
    
    CCSequence* sequeneAction=CCSequence::create(actionArray);
    this->runAction(sequeneAction);
}

void NormalAnt::endMove(CCPoint point,float time){
    CCMoveTo* moveTo=CCMoveTo::create(time, point);
    CCCallFuncN* callBackIdle=CCCallFuncN::create(this, callfuncN_selector(NormalAnt::CallFucnCallback2));
    
    CCArray* actionArray=CCArray::create();
    actionArray->addObject(moveTo);
    actionArray->addObject(callBackIdle);
    
    CCSequence* sequeneAction=CCSequence::create(actionArray);
    this->runAction(sequeneAction);
}

void NormalAnt::CallFucnCallback1(CCObject* pSender)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    this->changeDirection();
    switch (getRand(0,2)) {
        case 0:
            this->setAnimation("carrying pose 1", true,0);
            break;
        case 1:
            this->setAnimation("carrying pose 2", true,0);
            break;
        case 2:
            this->setAnimation("carrying pose 3", true,0);
            break;
        default:
            break;
    }
    //this->setAnimation("carrying pose 3", true,0);
    this->stopAllActions();
    this->endMove(startPoint,ccpDistance(this->getPosition(),startPoint)/130);
}

void NormalAnt::CallFucnCallback2(CCObject* pSender)
{
    //CCSprite* sp3 = (CCSprite*)pSender;
    this->removeFromParent();
}

void NormalAnt::CallFucnCallbackLizi(CCObject* pSender)
{
    pNode->myFenshuLabel->setString(CCString::createWithFormat("score：%d",ScoresManager::getInstance().getMyTotalScores())->getCString());
}

void NormalAnt::setDirection(RoleDirection rDirection){
    roleDirection=rDirection;
    switch (roleDirection) {
        case kRoleDirectionLeft:
            this->setScaleX(-0.5);
            break;
        case kRoleDirectionRight:
            this->setScaleX(0.5);
            break;
        default:
            break;
    }
}

void NormalAnt::onEnter()
{
    CCNode::onEnter();
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
}

void NormalAnt::onExit()
{
    CCNode::onExit();
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
}

bool NormalAnt::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    if (!isTouchMe(pTouch))
	{
		return false;
	}
	CCLOG("点击了！！！！");
	return true;
}

//5, 10, 10-n-r, 10-s-r
void NormalAnt::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent ){
    ScoresManager::getInstance().addMyScores(1);
    
    CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::create("touch.plist");
    emitter1->setPosition(ccp( boundingBox().origin.x+10,    boundingBox().origin.y+20));    // 设置发射粒子的位置
    emitter1->setAutoRemoveOnFinish(true);                          // 完成后制动移除
    emitter1->setDuration(ccpDistance(this->getPosition(),pNode->myFenshuLabel->getPosition())/400+0.5);                                      // 设置粒子系统的持续时间秒
    pNode->addChild(emitter1, 0, 1);
    CCMoveTo* moveTo=CCMoveTo::create(ccpDistance(this->getPosition(),pNode->myFenshuLabel->getPosition())/400,pNode->myFenshuLabel->getPosition());
    CCCallFuncN* callBackLizi=CCCallFuncN::create(this, callfuncN_selector(NormalAnt::CallFucnCallbackLizi));
    CCArray* actionArray=CCArray::create();
    actionArray->addObject(moveTo);
    actionArray->addObject(callBackLizi);
    CCSequence* sequeneAction=CCSequence::create(actionArray);
    emitter1->runAction(sequeneAction);
    
    CCParticleSystem * p1=CCParticleFire::create();
    p1->setPosition(0, 50);
    p1->setPosVar(ccp(10, 20));
    p1->setLife(1);
    p1->setStartSize(35);
    p1->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));
    p1->setAutoRemoveOnFinish(false);
    this->addChild(p1,100);
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);
    
    this->clearAnimation(0);
    this->setAnimation("run & cry", true,1);
    
    //this->setAnimation("struck pose", true,1);
    //this->setMix("struck pose", "run & cry", 0.4);
    this->changeDirection();
    this->stopAllActions();
    this->endMove(startPoint,ccpDistance(this->getPosition(),startPoint)/130);
}

bool NormalAnt::isTouchMe( CCTouch* pTouch )
{
    //获得点击的OpenGL的世界坐标值
    CCPoint touchPoint = pTouch->getLocation();
    //将点击的位置转换成父元素坐标系中的相对坐标
    CCPoint pt=getParent()->convertToNodeSpace(touchPoint);
//    CCLOG("点击的坐标X：%f  Y:%f",pt.x,pt.y);
    //得到自己在父元素坐标系中的位置范围
    CCRect rect=boundingBox();
//    rect.origin.x = rect.origin.x;
//    rect.origin.y = rect.origin.y;
    //CCLOG("自己的坐标X：%f  Y:%f",rect.origin.x,rect.origin.y);
    //判断是否点击落在自己的范围当中， 以上判断全是在父元素坐标系中进行计算
    //rect.containsPoint(pt);
    //42.4  65.5
    if(pt.x >= rect.origin.x-rect.size.width && pt.x <= rect.origin.x+rect.size.width*2
       && pt.y >= rect.origin.y && pt.y <= rect.origin.y+rect.size.width*2)
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
        return true;
    }
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("miss.wav");
    return false;
}

void NormalAnt::changeDirection(){
    switch (roleDirection) {
        case kRoleDirectionLeft:
            setDirection(kRoleDirectionRight);
            break;
        case kRoleDirectionRight:
            setDirection(kRoleDirectionLeft);
            break;
        default:
            break;
    }
}

int NormalAnt::getRand(int start,int end)
{
    float i = CCRANDOM_0_1()*(end-start+1)+start;  //产生一个从start到end间的随机数
    return (int)i;
}

void NormalAnt::checkBox()
{
    CCLOG("宽度：%f",this->boundingBox().size.width);
    CCLOG("高度：%f",this->boundingBox().size.height);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCRect projectileRect=boundingBox();
    CCRect targetRect = CCRectMake(
                                   visibleSize.width/2-57,
                                   visibleSize.height/2+10,
                                   90,
                                   70);

    if (projectileRect.intersectsRect(targetRect))
    {
//        ScoresManager::getInstance().addMyScores(1);
//        pNode->myFenshuLabel->setString(CCString::createWithFormat("得分：%d",ScoresManager::getInstance().getMyTotalScores())->getCString());
        //CCLOG("进入范围了");
        if (ScoresManager::getInstance().getCakeTotalScores()>0) {
            pNode->cakeFenshuLabel->setString(CCString::createWithFormat("sweet HP：%d",ScoresManager::getInstance().subCakeScores(1))->getCString());
        }
        
        if (ScoresManager::getInstance().getCakeTotalScores()==2) {
            CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
            CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("twoxuebg.mp3", true);
        }
        
        if(ScoresManager::getInstance().getCakeTotalScores()==0){
            CCDirector* pDirector = CCDirector::sharedDirector();
            pDirector->getTouchDispatcher()->removeDelegate(this);
            if (!pNode->isOver) {
                pNode->isOver = true;
                pNode->unscheduleAllSelectors();
                pNode->m_pauseDialog->show();
                CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
                CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("dead.mp3", true);
            }
        }
        CallFucnCallback1(this);
        unschedule(schedule_selector(NormalAnt::checkBox));
    }
    
    if(ScoresManager::getInstance().getCakeTotalScores()==0){
        CCDirector* pDirector = CCDirector::sharedDirector();
        pDirector->getTouchDispatcher()->removeDelegate(this);
    }
}

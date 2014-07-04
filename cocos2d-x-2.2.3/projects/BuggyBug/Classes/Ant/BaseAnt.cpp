//
//  BaseAnt.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-4-28.
//
//

#include "BaseAnt.h"
#include "UITools.h"
#include "GamePlayScene.h"
#include "SimpleAudioEngine.h"
BaseAnt* BaseAnt::createWithType(AntType antType){
    SkeletonData * skDate = ScoresManager::getInstance().getSpineData(antType);
    BaseAnt* node = createWithData(skDate);
    node->setAntType(antType);
    return node;
}

void BaseAnt::setAntType(AntType antType){
    m_antType = antType;
}

BaseAnt* BaseAnt::createWithFile (const char* skeletonDataFile, Atlas* atlas, float scale) {
	BaseAnt* node = new BaseAnt(skeletonDataFile, atlas, scale);
	node->autorelease();
	return node;
}

BaseAnt::BaseAnt (const char* skeletonDataFile, Atlas* atlas, float scale)
: CCSkeletonAnimation(skeletonDataFile, atlas, scale) {
	addAnimationState();
}

BaseAnt* BaseAnt::createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale) {
	BaseAnt* node = new BaseAnt(skeletonDataFile, atlasFile, scale);
	node->autorelease();
	return node;
}

BaseAnt::BaseAnt (const char* skeletonDataFile, const char* atlasFile, float scale)
: CCSkeletonAnimation(skeletonDataFile, atlasFile, scale) {
	addAnimationState();
}

BaseAnt* BaseAnt::createWithData (SkeletonData* skeletonData) {
	BaseAnt* node = new BaseAnt(skeletonData);
	node->autorelease();
	return node;
}

BaseAnt::BaseAnt (SkeletonData *skeletonData)
: CCSkeletonAnimation(skeletonData) {
	addAnimationState();
}

static GamePlayScene* pNode;

BaseAnt::~BaseAnt(){
   
}

void BaseAnt::onEnterTransitionDidFinish()
{
    pNode = (GamePlayScene*)getParent();
    schedule(schedule_selector(BaseAnt::myUpdate));
    this->initSelf();
    this->initActions();
//    this->initSelf();
//    this->initActions();
}

void BaseAnt::initActions(){
    CCSize mysize=CCDirector::sharedDirector()->getWinSize();
    if (startPoint.x>mysize.width/2) {
        setDirection(kRoleDirectionLeft);
    }else{
        setDirection(kRoleDirectionRight);
    }
    //this->starAction();
    this->antMove(ccp(mysize.width/2,mysize.height/2),ccpDistance(this->getPosition(),ccp(mysize.width/2,mysize.height/2))/goInSpeed);
}

void BaseAnt::initSelf(){
    UILoaderAnt *antLoader = (UILoaderAnt*)ConfigCache::sharedConfigCache()->getConfig(xml_type_ant);
    AntStruct ant = antLoader->getRole(m_antType);
    AntPropertyIt antIt;
    for (antIt = ant.attributes.begin(); antIt != ant.attributes.end(); ++antIt) {
        switch ((AntAttribute)antIt->first) {
            case aTotalBlood:
                this->totalBlood=(AntAttribute)atoi((antIt->second.value).c_str());
                break;
            case aCurrentBlood:
                this->currentBlood=(AntAttribute)atoi((antIt->second.value).c_str());
                break;
            case aDamage:
                this->damage=(AntAttribute)atoi((antIt->second.value).c_str());
                break;
            case aGoInSpeed:
                this->goInSpeed=(AntAttribute)atoi((antIt->second.value).c_str());
                break;
            case aComeBackSpeed:
                this->comeBackSpeed=(AntAttribute)atoi((antIt->second.value).c_str());
                break;
            case aScore:
                this->score = (AntAttribute)atoi((antIt->second.value).c_str());
            default:
                break;
        }
    }
    
    this->setAnimation("walk", true,0);
    this->setSkin("male");
    this->setScale(0.5);
    roleState = kRoleStateWalk;
}

void BaseAnt::onEnter()
{
    CCNode::onEnter();
    setTouchEnabled(true);
    
}

void BaseAnt::onExit()
{
    CCNode::onExit();
    setTouchEnabled(false);
}

void BaseAnt::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher *dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	dispatcher->addTargetedDelegate(this,m_nPriority,true);
}

void BaseAnt::setTouchEnabled( bool enable )
{
	if( m_isTouchEnabled != enable)
	{
		m_isTouchEnabled = enable;
		if( m_isTouchEnabled)
		{
			registerWithTouchDispatcher();
		}
		else
		{
			CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		}
	}
}

bool BaseAnt::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    if (!isTouchMe(pTouch))
	{
		return false;
	}
	CCLOG("点击了！！！！");
	return true;
}

void BaseAnt::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent ){
    //每点击一次蚂蚁就减少1点血量
    currentBlood = currentBlood - 1;
    //每点击一次蚂蚁就去检查一下血量的剩余
    this->checkAntHP();
}

//判断是否点击到蚂蚁
bool BaseAnt::isTouchMe( CCTouch* pTouch )
{
    //获得点击的OpenGL的世界坐标值
    CCPoint touchPoint = pTouch->getLocation();
    //将点击的位置转换成父元素坐标系中的相对坐标
    CCPoint pt=getParent()->convertToNodeSpace(touchPoint);
    CCLOG("点击的坐标X：%f  Y:%f",pt.x,pt.y);
    //得到自己在父元素坐标系中的位置范围
    CCRect rect=boundingBox();
    if(pt.x >= rect.origin.x-rect.size.width && pt.x <= rect.origin.x+rect.size.width*2
       && pt.y >= rect.origin.y && pt.y <= rect.origin.y+rect.size.width*2)
    {
        //CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("hit.wav");
        //CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("NotthefinalANTTAP.wav");
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("button.mp3");
        
        return true;
    }else{
        //CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("miss.wav");
        //CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("NotthefinalANTTAP.wav");
        return false;
    }
    
    
}

void BaseAnt::checkAntHP(){
    switch (currentBlood) {
        case 0:
        {
            roleState = kRoleStateCryRun;
            this->setAnimation("run & cry", true,0);
            this->setTouchEnabled(false);//取消触摸
            
            this->changeDirection();//改变蚂蚁的方向
            this->antMove(startPoint,ccpDistance(this->getPosition(),startPoint)/comeBackSpeed);
            
            ScoresManager::getInstance().addMyScores(score);
            pNode->playLayer->m_ScoresLabel->setString(CCString::createWithFormat("%d",ScoresManager::getInstance().getMyTotalScores())->getCString());
            
            CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::create("touch.plist");
            //emitter1->setPosition(ccp( boundingBox().origin.x+10,    boundingBox().origin.y+20));    // 设置发射粒子的位置
            emitter1->setAutoRemoveOnFinish(true);                          // 完成后制动移除
            
            CCPoint point = pNode->playLayer->m_TitleBgSprite->getPosition();
            point.x = point.x-86;
            point.y = point.y+31;
            
            emitter1->setPosition(point);
            emitter1->setDuration(1);                                      // 设置粒子系统的持续时间秒
            pNode->addChild(emitter1, 300, 1);
            
            //CCMoveTo* moveTo=CCMoveTo::create(ccpDistance(this->getPosition(),pNode->playLayer->m_TitleBgSprite->getPosition())/400,point);
            //CCCallFuncN* callBackLizi=CCCallFuncN::create(this, callfuncN_selector(NormalAnt::CallFucnCallbackLizi));
            //CCArray* actionArray=CCArray::create();
            //actionArray->addObject(moveTo);
            //actionArray->addObject(callBackLizi);
            //CCSequence* sequeneAction=CCSequence::create(actionArray);
            //emitter1->runAction(sequeneAction);
            
            
            //pNode->myFenshuLabel->setString(CCString::createWithFormat("score：%d",ScoresManager::getInstance().getMyTotalScores())->getCString());
            
//            CCFiniteTimeAction *actionOne = CCSequence::create(
//                                                               CCDelayTime::create(0.5f),
//                                                               CCCallFunc::create(this,callfunc_selector(BaseAnt::AntCryBackCall)),
//                                                               NULL  
//                                                               );
//            this->runAction(actionOne);
        }
            break;
            
        default:
            break;
    }
}

void BaseAnt::AntCryBackCall(CCObject* pSender){
//    this->setAnimation("run & cry", true,0);
//    this->changeDirection();//改变蚂蚁的方向
//    this->antMove(startPoint,ccpDistance(this->getPosition(),startPoint)/comeBackSpeed);
}

void BaseAnt::changeDirection(){
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

void BaseAnt::setDirection(RoleDirection rDirection){
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

void BaseAnt::antMove(CCPoint point,float time){
    this->stopAllActions();
    CCMoveTo* moveTo=CCMoveTo::create(time, point);
    CCCallFuncN* callBackIdle=CCCallFuncN::create(this,callfuncN_selector(BaseAnt::MoveToCallFucn));
    
    CCArray* actionArray=CCArray::create();
    actionArray->addObject(moveTo);
    actionArray->addObject(callBackIdle);
    
    CCSequence* sequeneAction=CCSequence::create(actionArray);
    this->runAction(sequeneAction);
}

void BaseAnt::MoveToCallFucn(CCObject* pSender)
{
    switch (roleState) {
        case kRoleStateWalk:
        {
            this->changeDirection();
            switch (UITools::getRandForInt(0,2)) {
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
            roleState = kRoleStateRun;
            this->antMove(startPoint,ccpDistance(this->getPosition(),startPoint)/comeBackSpeed);
        }
            break;
        case kRoleStateRun:
        {
            this->removeFromParent();
        }
            break;
        case kRoleStateCryRun:
        {
            this->removeFromParent();
        }
            break;
        default:
            break;
    }
}

void BaseAnt::myUpdate()
{
    //CCLOG("宽度：%f",this->boundingBox().size.width);
    //CCLOG("高度：%f",this->boundingBox().size.height);
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCRect projectileRect=boundingBox();
    CCRect targetRect = CCRectMake(
                                   visibleSize.width/2-57,
                                   visibleSize.height/2+10,
                                   90,
                                   70);
    
    if (projectileRect.intersectsRect(targetRect))
    {
        this->setTouchEnabled(false);
        if (ScoresManager::getInstance().getCakeTotalScores()>0) {
            //监测碰撞，减少cake的HP根据蚂蚁的力量
            pNode->playLayer->m_HPLabel->setString(CCString::createWithFormat("%d",ScoresManager::getInstance().subCakeScores(damage))->getCString());
            //pNode->cakeFenshuLabel->setString(CCString::createWithFormat("sweet HP：%d",ScoresManager::getInstance().subCakeScores(damage))->getCString());
            if (ScoresManager::getInstance().cakeScores<0) {
                ScoresManager::getInstance().cakeScores=0;
            }
            if (ScoresManager::getInstance().getCakeTotalScores()==2) {
                CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
                //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("twoxuebg.mp3", true);
            }
        }
        if(ScoresManager::getInstance().getCakeTotalScores()==0){
            this->setTouchEnabled(false);
            pNode->unscheduleAllSelectors();
            if (!pNode->m_pauseDialog->isVisible()) {
                pNode->m_pauseDialog->show();
                CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
                //CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("dead.mp3", true);
            }
        }
        MoveToCallFucn(this);
        unschedule(schedule_selector(BaseAnt::myUpdate));
    }
    
    if(ScoresManager::getInstance().getCakeTotalScores()==0){
        this->setTouchEnabled(false);
    }
}


#include "PauseDialogLayer.h"
#include "GamePlayScene.h"
#include "ScoresManager.h"
#include "GameMianScene.h"
#include "SimpleAudioEngine.h"

void PauseDialogLayer::sel_resume(CCObject *pSender)
{
	CCLOG("重新开始");
    scheduleOnce(schedule_selector(PauseDialogLayer::resetGame),0.5);
    hide();
}

void PauseDialogLayer::sel_goBackHome(CCObject *pSender)
{
    ScoresManager::getInstance().resetScores();
    ScoresManager::getInstance().selectBoci(1);
    
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCTransitionMoveInT* transition = CCTransitionMoveInT ::create(0.7f,GameMianScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
    hide();
}

void PauseDialogLayer::show()
{
	this->setVisible(true);
	CCMenu * menu = (CCMenu *)this->getChildByTag(200);
	//this->runAction(CCTintTo::actionWithDuration(.3, 0,0,0));
	this->runAction(CCFadeTo::create(0.3f , 200));
	menu->setPosition(CCPointCenterTop);
	menu->runAction(CCEaseSineInOut::create(CCMoveTo::create(.3f,  CCPointCenter)));
    jieguoLabel->setString(CCString::createWithFormat("score:%d",ScoresManager::getInstance().getMyTotalScores())->getCString());
    
    CCParticleSystemQuad *emitter1 = CCParticleSystemQuad::create("scroce.plist");
    emitter1->setPosition(ccp(CCScreenWidth/2 , -200));    // 设置发射粒子的位置
    emitter1->setAutoRemoveOnFinish(true);   // 完成后制动移除
    //emitter1->setDuration(100);            // 设置粒子系统的持续时间秒
    this->addChild(emitter1, 300, 1);
    
    CCSprite *scSp = CCSprite::create("HUD_98.png");
    emitter1->addChild(scSp);
    
    CCRotateTo *rotate = CCRotateTo::create(1.0f,360);
    scSp->runAction(CCRepeatForever::create(rotate));
    
    CCMoveTo* moveTo=CCMoveTo::create(ccpDistance(this->getPosition(),CCPointCenter)/400,ccp(CCScreenWidth/2 , CCScreenHeight/1.5));
    //CCCallFuncN* callBackLizi=CCCallFuncN::create(this, callfuncN_selector(NormalAnt::CallFucnCallbackLizi));
    CCArray* actionArray=CCArray::create();
    actionArray->addObject(moveTo);
    //actionArray->addObject(callBackLizi);
    CCSequence* sequeneAction=CCSequence::create(actionArray);
    emitter1->runAction(sequeneAction);
    
    this->setTouchEnabled(true);
}

void PauseDialogLayer::hide()
{
	//this->runAction(CCTintTo::actionWithDuration(.3, 0,0,0));
	this->runAction(CCFadeTo::create(0.3f , 0));
	CCMenu * menu = (CCMenu *)this->getChildByTag(200);
	menu->runAction(CCEaseBackInOut::create(CCMoveTo::create(.8f,  ccp(CCScreenWidth/2 , -200))));
	
    CCLabelTTF * labelOne = (CCLabelTTF*)this->getChildByTag(300);
    labelOne->runAction(CCEaseBackInOut::create(CCMoveTo::create(.8f,  ccp(CCScreenWidth/2 , -200))));
    
    CCLabelTTF * labelTwo = (CCLabelTTF*)this->getChildByTag(400);
    labelTwo->runAction(CCEaseBackInOut::create(CCMoveTo::create(.8f,  ccp(CCScreenWidth/2 , -200))));
    
    this->setTouchEnabled(false);
}

CCLayer * PauseDialogLayer::layer(CCLayer * parent)
{
	PauseDialogLayer * pauseDlg =  new PauseDialogLayer;
	ccColor4B t = {0,0,0,100};
	pauseDlg->initWithColor(t);
	pauseDlg->init();
	pauseDlg->autorelease();
	pauseDlg->m_gameScene = parent;
	return pauseDlg;
}

void PauseDialogLayer::setWin()
{
	CCMenuItemToggle * toggle = (CCMenuItemToggle *)this->getChildByTag(102);
	toggle->setSelectedIndex(0);
}

void PauseDialogLayer::setLose()
{
	CCMenuItemToggle * toggle = (CCMenuItemToggle *)this->getChildByTag(102);
	toggle->setSelectedIndex(1);
}



bool PauseDialogLayer::init()
{
    this->setTouchEnabled(false);
    titleLabel = CCLabelTTF::create("Game Over", "AmericanTypewriter-Bold", 40);
    titleLabel->setTag(300);
    titleLabel->setPosition(ccp(CCScreenWidth/2,CCScreenHeight/2+200));
    this->addChild(titleLabel, 1);
    
    jieguoLabel = CCLabelTTF::create(CCString::createWithFormat("score:%d",ScoresManager::getInstance().addMyScores(0))->getCString(), "Arial", 26);
    jieguoLabel->setTag(400);
    jieguoLabel->setPosition(ccp(CCScreenWidth/2,CCScreenHeight/2+150));
    this->addChild(jieguoLabel, 1);

	CCMenuItemFont::setFontSize(30);
	CCMenuItemFont * item_restart = CCMenuItemFont::create("TYR AGAIN" , this, menu_selector(PauseDialogLayer::sel_resume));

    CCMenuItemFont::setFontSize(30);
	CCMenuItemFont * item_restart2 = CCMenuItemFont::create("MAIN SCENE" , this, menu_selector(PauseDialogLayer::sel_goBackHome));
	
	CCMenu * menu = CCMenu::create(item_restart,item_restart2 , NULL);
	menu->alignItemsVerticallyWithPadding(50);
	menu->setTag(200);
	this->addChild(menu );

	CCMenuItemFont::setFontSize(10);
	//menu->setPosition( CCPointCenterTop);
	//menu->runAction(CCEaseBackInOut::actionWithAction(CCMoveTo::actionWithDuration(0.6f,CCPointCenter)));
	return true;
}

void PauseDialogLayer::resetGame(CCObject* pSender){
    ScoresManager::getInstance().resetScores();
    ScoresManager::getInstance().selectBoci(1);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCScene *scene1 = GamePlayScene::scene();
    CCDirector::sharedDirector()->replaceScene(scene1);
}

bool PauseDialogLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void PauseDialogLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void PauseDialogLayer::onEnter()
{
    CCLayer::onEnter();
}

void PauseDialogLayer::onExit()
{
    CCLayer::onExit();
}

void PauseDialogLayer::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher *dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	dispatcher->addTargetedDelegate(this,m_nPriority,true);
}

void PauseDialogLayer::setTouchEnabled( bool enable )
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

#include "PauseLayer.h"
#include "GamePlayScene.h"
#include "ScoresManager.h"
#include "GameMianScene.h"
#include "SimpleAudioEngine.h"

void PauseLayer::sel_goon(CCObject *pSender)
{
	CCLOG("继续游戏");
    CCDirector::sharedDirector()->resume();
    hide();
}

void PauseLayer::sel_resume(CCObject *pSender)
{
	CCLOG("重新开始");
    scheduleOnce(schedule_selector(PauseLayer::resetGame),0.5);
    CCDirector::sharedDirector()->resume();
    hide();
}

void PauseLayer::sel_goBackHome(CCObject *pSender)
{
    ScoresManager::getInstance().resetScores();
    ScoresManager::getInstance().selectBoci(1);
    
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCTransitionMoveInT* transition = CCTransitionMoveInT ::create(0.7f,GameMianScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
    CCDirector::sharedDirector()->resume();
    hide();
}

void PauseLayer::show()
{
	this->setVisible(true);
    //this->runAction(CCFadeTo::create(0.3f , 200));
    this->setOpacity(200);
    
	CCMenu * menu = (CCMenu *)this->getChildByTag(200);
	menu->setPosition(CCPointCenter);
    
    CCLabelTTF * labelOne = (CCLabelTTF*)this->getChildByTag(300);
    labelOne->setPosition(ccp(CCScreenWidth/2,CCScreenHeight/2+200));
    
    this->setTouchEnabled(true);
}

void PauseLayer::hide()
{
	//this->runAction(CCTintTo::actionWithDuration(.3, 0,0,0));
	this->runAction(CCFadeTo::create(0.3f , 0));
	CCMenu * menu = (CCMenu *)this->getChildByTag(200);
	menu->runAction(CCEaseBackInOut::create(CCMoveTo::create(.8f,  ccp(CCScreenWidth/2 , -200))));
	
    CCLabelTTF * labelOne = (CCLabelTTF*)this->getChildByTag(300);
    labelOne->runAction(CCEaseBackInOut::create(CCMoveTo::create(.8f,  ccp(CCScreenWidth/2 , -200))));
    
    this->setTouchEnabled(false);
}

CCLayer * PauseLayer::layer(CCLayer * parent)
{
	PauseLayer * pauseDlg =  new PauseLayer;
	ccColor4B t = {0,0,0,100};
	pauseDlg->initWithColor(t);
	pauseDlg->init();
	pauseDlg->autorelease();
	pauseDlg->m_gameScene = parent;
	return pauseDlg;
}

void PauseLayer::setWin()
{
	CCMenuItemToggle * toggle = (CCMenuItemToggle *)this->getChildByTag(102);
	toggle->setSelectedIndex(0);
}

void PauseLayer::setLose()
{
	CCMenuItemToggle * toggle = (CCMenuItemToggle *)this->getChildByTag(102);
	toggle->setSelectedIndex(1);
}



bool PauseLayer::init()
{
    this->setTouchEnabled(false);
    titleLabel = CCLabelTTF::create("Buggy Bug", "AmericanTypewriter-Bold", 40);
    titleLabel->setTag(300);
    titleLabel->setPosition(ccp(CCScreenWidth/2,CCScreenHeight/2+200));
    this->addChild(titleLabel, 1);

    CCMenuItemFont::setFontSize(30);
	CCMenuItemFont * item_restart1 = CCMenuItemFont::create("RESUME GAME" , this, menu_selector(PauseLayer::sel_goon));
    
	CCMenuItemFont::setFontSize(30);
	CCMenuItemFont * item_restart2 = CCMenuItemFont::create("TYR AGAIN" , this, menu_selector(PauseLayer::sel_resume));

    CCMenuItemFont::setFontSize(30);
	CCMenuItemFont * item_restart3 = CCMenuItemFont::create("MAIN SCENE" , this, menu_selector(PauseLayer::sel_goBackHome));
	
	CCMenu * menu = CCMenu::create(item_restart1,item_restart2,item_restart3 , NULL);
	menu->alignItemsVerticallyWithPadding(30);
	menu->setTag(200);
    menu->setPosition(CCPointCenter);
	//menu->runAction(CCEaseSineInOut::create(CCMoveTo::create(.3f,  CCPointCenter)));
	this->addChild(menu );

	CCMenuItemFont::setFontSize(10);
	//menu->setPosition( CCPointCenterTop);
	//menu->runAction(CCEaseBackInOut::actionWithAction(CCMoveTo::actionWithDuration(0.6f,CCPointCenter)));
	return true;
}

void PauseLayer::resetGame(CCObject* pSender){
    ScoresManager::getInstance().resetScores();
    ScoresManager::getInstance().selectBoci(1);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCScene *scene1 = GamePlayScene::scene();
    CCDirector::sharedDirector()->replaceScene(scene1);
}

bool PauseLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void PauseLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void PauseLayer::onEnter()
{
    CCLayer::onEnter();
    //setTouchEnabled(true);
}

void PauseLayer::onExit()
{
    CCLayer::onExit();
    //setTouchEnabled(false);

}

void PauseLayer::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher *dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	dispatcher->addTargetedDelegate(this,m_nPriority,true);
}

void PauseLayer::setTouchEnabled( bool enable )
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

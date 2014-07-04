#include "pauseDialog.h"
#include "rwMacro.h"
#include "HelloWorldScene.h"
#include "ScoresManager.h"
#include "SimpleAudioEngine.h"
#include "GameMianScene.h"

void PauseDialog::sel_resume(CCObject *pSender)
{
	CCLOG("重新开始");
    scheduleOnce(schedule_selector(PauseDialog::resetGame),0.5);
    hide();
}

void PauseDialog::sel_goBackHome(CCObject *pSender)
{
    ScoresManager::getInstance().resetScores();
    ScoresManager::getInstance().selectBoci(1);
    
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCTransitionMoveInT* transition = CCTransitionMoveInT ::create(0.7f,GameMianScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
    hide();
}

void PauseDialog::show()
{
	this->setVisible(true);
	CCMenu * menu = (CCMenu *)this->getChildByTag(200);
	//this->runAction(CCTintTo::actionWithDuration(.3, 0,0,0));
	this->runAction(CCFadeTo::create(0.3f , 200));
	menu->setPosition(CCPointCenterTop);
	menu->runAction(CCEaseSineInOut::create(CCMoveTo::create(.3f,  CCPointCenter)));
    jieguoLabel->setString(CCString::createWithFormat("score:%d",ScoresManager::getInstance().getMyTotalScores())->getCString());
}

void PauseDialog::hide()
{
	//this->runAction(CCTintTo::actionWithDuration(.3, 0,0,0));
	this->runAction(CCFadeTo::create(0.3f , 0));
	CCMenu * menu = (CCMenu *)this->getChildByTag(200);
	menu->runAction(CCEaseBackInOut::create(CCMoveTo::create(.8f,  ccp(CCScreenWidth/2 , -200))));
	
    CCLabelTTF * labelOne = (CCLabelTTF*)this->getChildByTag(300);
    labelOne->runAction(CCEaseBackInOut::create(CCMoveTo::create(.8f,  ccp(CCScreenWidth/2 , -200))));
    
    CCLabelTTF * labelTwo = (CCLabelTTF*)this->getChildByTag(400);
    labelTwo->runAction(CCEaseBackInOut::create(CCMoveTo::create(.8f,  ccp(CCScreenWidth/2 , -200))));
}

CCLayer * PauseDialog::layer(CCLayer * parent)
{
	PauseDialog * pauseDlg =  new PauseDialog;
	ccColor4B t = {0,0,0,100};
	pauseDlg->initWithColor(t);
	pauseDlg->init();
	pauseDlg->autorelease();
	pauseDlg->m_gameScene = parent;
	return pauseDlg;
}

void PauseDialog::setWin()
{
	CCMenuItemToggle * toggle = (CCMenuItemToggle *)this->getChildByTag(102);
	toggle->setSelectedIndex(0);
}

void PauseDialog::setLose()
{
	CCMenuItemToggle * toggle = (CCMenuItemToggle *)this->getChildByTag(102);
	toggle->setSelectedIndex(1);
}



bool PauseDialog::init()
{
    this->setTouchEnabled(true);
    titleLabel = CCLabelTTF::create("Game Over", "AmericanTypewriter-Bold", 40);
    titleLabel->setTag(300);
    titleLabel->setPosition(ccp(CCScreenWidth/2,CCScreenHeight/2+200));
    this->addChild(titleLabel, 1);
    
    jieguoLabel = CCLabelTTF::create(CCString::createWithFormat("score:%d",ScoresManager::getInstance().addMyScores(0))->getCString(), "Arial", 26);
    jieguoLabel->setTag(400);
    jieguoLabel->setPosition(ccp(CCScreenWidth/2,CCScreenHeight/2+150));
    this->addChild(jieguoLabel, 1);

	CCMenuItemFont::setFontSize(30);
	CCMenuItemFont * item_restart = CCMenuItemFont::create("TYR AGAIN" , this, menu_selector(PauseDialog::sel_resume));

    CCMenuItemFont::setFontSize(30);
	CCMenuItemFont * item_restart2 = CCMenuItemFont::create("MAIN SCENE" , this, menu_selector(PauseDialog::sel_goBackHome));
	
	CCMenu * menu = CCMenu::create(item_restart,item_restart2 , NULL);
	menu->alignItemsVerticallyWithPadding(50);
	menu->setTag(200);
	this->addChild(menu );

	CCMenuItemFont::setFontSize(10);
	//menu->setPosition( CCPointCenterTop);
	//menu->runAction(CCEaseBackInOut::actionWithAction(CCMoveTo::actionWithDuration(0.6f,CCPointCenter)));
	return true;
}

void PauseDialog::resetGame(CCObject* pSender){
    ScoresManager::getInstance().resetScores();
    ScoresManager::getInstance().selectBoci(1);
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    CCScene *scene1 = HelloWorld::scene();
    CCDirector::sharedDirector()->replaceScene(scene1);
}

bool PauseDialog::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void PauseDialog::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void PauseDialog::onEnter()
{
    CCLayer::onEnter();
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void PauseDialog::onExit()
{
    CCLayer::onExit();
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->removeDelegate(this);

}

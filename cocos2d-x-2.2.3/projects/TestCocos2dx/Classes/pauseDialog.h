#ifndef _RW_PAUSEDIALGO_H
#define  _RW_PAUSEDIALGO_H

#include "cocos2d.h"
using namespace cocos2d;

class PauseDialog: public CCLayerColor
{
public:


	CREATE_FUNC(PauseDialog);
 
	virtual bool init();
	PauseDialog(){}
	~PauseDialog(){}
	static CCLayer * layer(CCLayer * parent);

	CCLayer * m_gameScene;
    CCLabelTTF* titleLabel;
    CCLabelTTF* jieguoLabel;

	void sel_resume(CCObject *pSender);
    void sel_goBackHome(CCObject *pSender);
	void show();
	void hide();
	void setWin();
	void setLose();
    void resetGame(CCObject* pSender);
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent );
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
};



#endif
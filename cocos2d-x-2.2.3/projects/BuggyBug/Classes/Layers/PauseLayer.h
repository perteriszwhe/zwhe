#ifndef _RW_PAUSE_H
#define  _RW_PAUSE_H

#include "cocos2d.h"
using namespace cocos2d;

class PauseLayer: public CCLayerColor
{
public:


	CREATE_FUNC(PauseLayer);
 
	virtual bool init();
	PauseLayer(){}
	~PauseLayer(){}
	static CCLayer * layer(CCLayer * parent);

	CCLayer * m_gameScene;
    CCLabelTTF* titleLabel;
    CCLabelTTF* jieguoLabel;

    void sel_goon(CCObject *pSender);
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
    
    void registerWithTouchDispatcher(void);
    
    void setTouchEnabled( bool enable );
    
    bool getTouchEnabled() const{ return m_isTouchEnabled; }
    
public:
    int m_nPriority = -100;
private:
	bool m_isTouchEnabled = false;
};



#endif
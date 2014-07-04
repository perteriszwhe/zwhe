#ifndef __UITOUCHSPRITE_H__
#define __UITOUCHSPRITE_H__

#include "cocos2d.h"

USING_NS_CC;

class UITouchSprite: public CCSprite, public CCTouchDelegate
{
public:
	UITouchSprite(void);
	~UITouchSprite(void);

	void setTouchEnabled(bool flag);
	bool getTouchEnabled() const { return m_isTouchEnabled; }

	void setEnabled(bool flag);
	bool getEnabled() const{ return m_isEnabled; }

	void setPriority(int priority){ m_nPriority = priority; }
	int	getPriority() const{ return m_nPriority; }

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) ;
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	void registerWithTouchDispatcher(void);

	void setClickCallback(CCCallFuncN *callback);

	virtual bool initWithSpriteFrames(CCSpriteFrame *normalFrame,CCSpriteFrame *selectFrame);

	void setNormalSpriteFrame(CCSpriteFrame *frame);
	void setSelectSpriteFrame(CCSpriteFrame *frame);

	static UITouchSprite* create(const char *img);

	static UITouchSprite* create(const char *normalImg,const char *selectImg);
	static UITouchSprite* create(CCSpriteFrame *normalFrame,CCSpriteFrame *selectFrame);
    int				m_nPriority;

private:

	void select();
	void unselect();

private:
	bool			m_isTouchEnabled;
	bool			m_isEnabled;
	CCCallFuncN		*m_clickCallback;
	CCSpriteFrame	*m_normalFrame;
	CCSpriteFrame	*m_selectFrame;
};

#endif



#ifndef __UIPROGRESS_H__
#define __UIPROGRESS_H__

#include "cocos2d.h"

USING_NS_CC;

class UIProgress: public CCNode
{
public:
	UIProgress(void);
	~UIProgress(void);

	bool initWithFile(const char *bgImg,const char *borderImg,const char *proImg,bool isZorder);

	void setBackground(const char *img);
	CCSprite* getBackgroundSprite() const{ return m_bgSprite; }

	void setBorder(const char *img);
	CCSprite* getBorderSprite() const { return m_borderSprite; }

	void setProgressImg(const char *img);
	CCSprite* getProgressSprite() { return m_progressSprite; }

	static UIProgress* create(const char *bgImg,const char *borderImg,const char *proImg,bool isZorder = false);
	static UIProgress* create(const char *borderImg,const char *proImg);
	static UIProgress* create(const char *proImg);

	void setCurrentProgress(float progress);
	float getCurrentProgress() const { return m_currentProgress; }

	void setColor(ccColor3B &color);

	bool isFinish();

private:
	CCProgressTimer			*m_progress;
	CCSprite				*m_bgSprite;
	CCSprite				*m_borderSprite;
	CCSprite				*m_progressSprite;
	float					m_currentProgress;
};

#endif




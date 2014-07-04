#ifndef __UINODE_H__
#define __UINODE_H__

#include "cocos2d.h"

USING_NS_CC;

class UILayout;
class UINode: public CCNode
{
public:
	UINode(void);
	virtual ~UINode(void);

	virtual bool initWithSize(CCSize &size);
	virtual bool initWithFile(const char *bgImg);
	virtual bool initWithSprite(CCSprite *sprite);
	virtual bool init();

	void setBackground(CCSprite *bgSprite);

	static UINode* create(CCSize &size);
	static UINode* create(CCSprite *bgSprite);
	static UINode* create(const char *bgImg);

	void setLayoutManager(UILayout *layout);

	void setBackgoundColor(ccColor4B &color);

protected:

	CCSprite		*m_bgSprite;
};

#endif



#ifndef __UILOADER_H__
#define __UILOADER_H__

#include "cocos2d.h"

using namespace cocos2d;

class Element;
class UILoader: public CCObject
{
public:
	UILoader(void);
	virtual ~UILoader(void);

	virtual bool initWithFileName(const char *filename);

	virtual void parseXml() = 0;

	virtual void loadData();

protected:
	Element		*m_rootElement;
};

#endif



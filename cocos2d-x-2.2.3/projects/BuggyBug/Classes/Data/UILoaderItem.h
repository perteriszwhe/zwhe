#ifndef __UILOADERITEM_H__
#define __UILOADERITEM_H__

#include "UILoader.h"
#include "structDef.h"

class UILoaderItem: public UILoader
{
private:
	MapItem			m_attributes;
public:
	UILoaderItem(void);
	~UILoaderItem(void);

	virtual void parseXml();

	static UILoaderItem* create(const char *filename);

	ItemStruct getRole(int key);

	ItemPropertyStruct getProperty(int roleKey,int proKey);
};

#endif



#ifndef __UILOADERANT_H__
#define __UILOADERANT_H__

#include "UILoader.h"
#include "structDef.h"

class UILoaderAnt: public UILoader
{
private:
	MapAnt			m_attributes;
public:
	UILoaderAnt(void);
	~UILoaderAnt(void);

	virtual void parseXml();

	static UILoaderAnt* create(const char *filename);

	AntStruct getRole(int key);

	AntPropertyStruct getProperty(int roleKey,int proKey);
};

#endif



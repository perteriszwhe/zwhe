#ifndef __UILOADERLEVEL_H__
#define __UILOADERLEVEL_H__

#include "UILoader.h"
#include "structDef.h"

class UILoaderLevel: public UILoader
{
private:
	MapLevel			m_attributes;
public:
	UILoaderLevel(void);
	~UILoaderLevel(void);

	virtual void parseXml();

	static UILoaderLevel* create(const char *filename);

	LevelStruct getRole(int key);

	LevelPropertyStruct getProperty(int roleKey,int proKey);
};

#endif



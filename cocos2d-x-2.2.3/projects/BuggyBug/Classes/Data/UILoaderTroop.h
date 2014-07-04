#ifndef __UILOADERTROOP_H__
#define __UILOADERTROOP_H__

#include "UILoader.h"
#include "structDef.h"

class UILoaderTroop: public UILoader
{
private:
	MapRole			m_attributes;
public:
	UILoaderTroop(void);
	~UILoaderTroop(void);

	virtual void parseXml();

	static UILoaderTroop* create(const char *filename);

	RoleStruct getRole(int key);

	PropertyStruct getProperty(int roleKey,int proKey);
};

#endif



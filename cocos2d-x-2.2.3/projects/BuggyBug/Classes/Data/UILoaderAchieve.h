#ifndef __UILOADERACHIEVE_H__
#define __UILOADERACHIEVE_H__

#include "UILoader.h"
#include "structDef.h"

class UILoaderAchieve: public UILoader
{
private:
	MapAchieve		m_mapAchieve;
public:
	UILoaderAchieve(void);
	~UILoaderAchieve(void);

	virtual void parseXml();

	static UILoaderAchieve* create(const char *filename);

	AchieveStruct getAchieve(int key);

	unsigned int size() const;
};

#endif



#ifndef __UILOADING_H__
#define __UILOADING_H__

#include "cocos2d.h"
using namespace cocos2d;

class UIProgress;
class UITaskManager;
class UILoading: public CCLayer
{
public:
	UILoading(void);
	~UILoading(void);

	static CCScene* scene();

	bool init();

	virtual void update(float delta);

	void loadResource();

	void taskAllFinishCallback(CCNode *node);

	void onTaskEndCallback(CCNode *node);

	CREATE_FUNC( UILoading);

private:
	UIProgress		*m_progress;
	UITaskManager	*m_taskManager;
	CCLabelTTF		*m_titleLabel;
};

#endif



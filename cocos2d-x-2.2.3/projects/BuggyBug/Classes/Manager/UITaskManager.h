#ifndef __UITASKMANAGER_H__
#define __UITASKMANAGER_H__

#include "cocos2d.h"
#include "UITask.h"
#include <vector>
USING_NS_CC;

class UITaskManager: public CCNode
{
	typedef std::vector<UITask*> VectorTask;
	typedef VectorTask::iterator VectorTaskIt;
private:
	VectorTask		m_allTask;
	VectorTaskIt	m_currentIterator;
	int				m_finishTaskCount;
	CCCallFuncN		*m_allFinishCallback;
	CCCallFuncN		*m_taskEndCallback;
	UITask			*m_currentTask;

	UITaskManager(void);
	~UITaskManager(void);

public:
	static UITaskManager* create(CCCallFuncN *callback);

	bool initCallback(CCCallFuncN *callback);

	void setAllFinishCallback(CCCallFuncN *callback);
	void setTaskEndCallback(CCCallFuncN *callback);

	UITask* getCurrentTask()const{ return m_currentTask; }

	void addTask(UITask *task);

	void doTask();

	virtual void update(float delta);

	void addXml(const char *filePath,int type);
	void addPlist(const char *filePath,const char *pvrccz);
	void addImage(const char *filePath);
    void addMusic(const char *filePath,int type);
    void addSpine(const char *jsonfile, const char *atlasFile, int type);

	unsigned int count() const{ return m_allTask.size(); }
	int	getCurrentTaskIndex() const { return m_finishTaskCount; }

	float getProgress();
};

#endif



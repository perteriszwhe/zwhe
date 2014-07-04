#include "UITaskManager.h"
#include "ConfigCache.h"

UITaskManager::UITaskManager(void)
	:m_finishTaskCount(0),
	m_allFinishCallback(NULL),
	m_taskEndCallback(NULL),
	m_currentTask(NULL)
{
}
UITaskManager::~UITaskManager(void)
{
	CC_SAFE_RETAIN( m_allFinishCallback);
	CC_SAFE_RETAIN( m_taskEndCallback);
	VectorTaskIt it = m_allTask.begin();
	while( it != m_allTask.end())
	{
		(*it)->release();
		m_allTask.erase(it);
	}
	m_allTask.clear();
}

void UITaskManager::addTask( UITask *task )
{
	task->retain();
	m_allTask.push_back(task);
}

void UITaskManager::doTask()
{
	m_currentIterator = m_allTask.begin();
	this->unscheduleUpdate();
	this->scheduleUpdate();
}
void UITaskManager::update( float delta )
{
	if( m_currentIterator != m_allTask.end())
	{
		m_finishTaskCount++;
		m_currentTask = (*m_currentIterator);
		m_currentTask->execute();
		m_currentIterator++;
		if( m_taskEndCallback)
			m_taskEndCallback->execute();
	}
	else
	{
		this->unscheduleUpdate();
		if( m_allFinishCallback)
			m_allFinishCallback->execute();
	}
}

void UITaskManager::addXml( const char *filePath ,int type)
{
	UITask *task = UITask::createXmlTask(filePath,type);
	addTask(task);
}

void UITaskManager::addPlist( const char *filePath,const char *pvrccz )
{
	UITask *task = UITask::createPlistTask(filePath,pvrccz);
	addTask(task);
}

void UITaskManager::addImage( const char *filePath )
{
	UITask *task = UITask::createImageTask(filePath);
	addTask(task);
}

void UITaskManager::addMusic( const char *filePath ,int type )
{
	UITask *task = UITask::createMusicTask(filePath, type);
	addTask(task);
}

void UITaskManager::addSpine( const char *jsonfile, const char *atlasFile, int type )
{
	UITask *task = UITask::createSpineTask(jsonfile, atlasFile, type);
	addTask(task);
}

float UITaskManager::getProgress()
{
	float progress = ((float)getCurrentTaskIndex() / (float)count()) * 100.0;
	return progress;
}

UITaskManager* UITaskManager::create( CCCallFuncN *callback )
{
	UITaskManager *manager = new UITaskManager;
	manager->initCallback(callback);
	manager->autorelease();
	return manager;
}

void UITaskManager::setAllFinishCallback( CCCallFuncN *callback )
{
	if( m_allFinishCallback != callback)
	{
		CC_SAFE_RELEASE( m_allFinishCallback);
		m_allFinishCallback = callback;
		CC_SAFE_RETAIN( m_allFinishCallback);
		m_allFinishCallback->setTarget(this);
	}
}

bool UITaskManager::initCallback( CCCallFuncN *callback )
{
	setAllFinishCallback(callback);
	return true;
}

void UITaskManager::setTaskEndCallback( CCCallFuncN *callback )
{
	if( m_taskEndCallback != callback)
	{
		CC_SAFE_RELEASE( m_taskEndCallback);
		m_taskEndCallback = callback;
		CC_SAFE_RETAIN( m_taskEndCallback);
		m_taskEndCallback->setTarget(this);
	}
}



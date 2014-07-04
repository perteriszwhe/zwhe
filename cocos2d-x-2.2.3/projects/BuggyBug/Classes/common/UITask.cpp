#include "UITask.h"
#include "ConfigCache.h"
#include "SimpleAudioEngine.h"
#include "ScoresManager.h"

UITask::UITask()
{

}
UITask::~UITask()
{
}

std::string UITask::getParam( const char *key )
{
	MapParamIt it = m_params.find(key);
	if( it != m_params.end())
	{
		return it->second;
	}
	return NULL;
}

UITask* UITask::create( task_type type)
{
	UITask *task = new UITask;
	task->init(type);
	task->autorelease();
	return task;
}

void UITask::init( task_type type )
{
	this->m_taskType = type;
}

void UITask::setParams( const char *key,const char *value )
{
	if( findParam(key))
	{
		deleteParam(key);
	}
	m_params.insert(std::make_pair(key,value));
}

bool UITask::findParam( const char *key )
{
	MapParamIt it = m_params.find(key);
	if( it != m_params.end())
	{
		return true;
	}
	return false;
}

void UITask::deleteParam( const char *key )
{
	MapParamIt it = m_params.find(key);
	if( it != m_params.end())
	{
		m_params.erase(it);
	}
}

UITask* UITask::createPlistTask( const char *filePath,const char *texturePath )
{
	UITask *task = new UITask;
	task->init(task_type_plist);
	task->setParams("filePath",filePath);
	task->setParams("texturePath",texturePath);
	task->autorelease();
	return task;
}

UITask* UITask::createXmlTask( const char *filePath ,int type)
{
	char buffer[3];
	sprintf(buffer,"%d",type);
	UITask *task = new UITask;
	task->init(task_type_xml);
	task->setParams("filePath",filePath);
	task->setParams("configType", buffer);
	task->autorelease();
	return task;
}

UITask* UITask::createMusicTask( const char *filePath ,int type)
{
	char buffer[3];
	sprintf(buffer,"%d",type);
	UITask *task = new UITask;
	task->init(task_type_music);
	task->setParams("filePath",filePath);
	task->setParams("musicType", buffer);
	task->autorelease();
	return task;
}

UITask* UITask::createSpineTask( const char *jsonFile, const char *atlasFile, int type )
{
	char buffer[3];
	sprintf(buffer,"%d",type);
	UITask *task = new UITask;
	task->init(task_type_spine);
    task->setParams("filePath",CCString::createWithFormat("%s+%s",jsonFile,atlasFile)->getCString());
	task->setParams("jsonFile",jsonFile);
    task->setParams("atlasFile",atlasFile);
	task->setParams("antType", buffer);
	task->autorelease();
	return task;
}

void UITask::execute()
{
	switch( m_taskType)
	{
	case task_type_plist:
		loadPlist();
		break;
	case task_type_xml:
		loadXml();
		break;
	case task_type_image:
		loadImage();
		break;
    case task_type_music:
        loadMusic();
        break;
    case task_type_spine:
        loadSpine();
        break;
            
	default:
		break;
	}
}

UITask* UITask::createImageTask( const char *filePath )
{
	UITask *task = new UITask;
	task->init(task_type_image);
	task->setParams("filePath",filePath);
	task->autorelease();
	return task;
}

void UITask::loadPlist()
{
	std::string filePath = getParam("filePath");
	std::string texturePath = getParam("texturePath");
	CCLOG("Loading Plist File: %s" , filePath.c_str());
	CCSpriteFrameCache *spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	if( spriteFrameCache->spriteFrameByName(filePath.c_str()))
		spriteFrameCache->removeSpriteFramesFromFile(filePath.c_str());
	spriteFrameCache->addSpriteFramesWithFile(filePath.c_str(),texturePath.c_str());
}

void UITask::loadXml()
{
	std::string filePath = getParam("filePath");
	std::string type = getParam("configType");
	CCLOG("Loading Xml File: %s", filePath.c_str());
	ConfigCache::sharedConfigCache()->addConfigForFile(filePath.c_str(),(config_type)atoi(type.c_str()));
}

void UITask::loadImage()
{
	std::string filePath = getParam("filePath");
	CCLOG("loading Image File: %s", filePath.c_str());
	CCTextureCache::sharedTextureCache()->addImage(filePath.c_str());
}

void UITask::loadMusic()
{
	std::string filePath = getParam("filePath");
	std::string type = getParam("musicType");
    
    if (std::atoi(type.c_str())==0) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect(filePath.c_str());
        CCLOG("Loading Effect File：%s", filePath.c_str());
    }else{
        CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(filePath.c_str());
        CCLOG("Loading BackGroundMusic File：%s", filePath.c_str());
    }
}

void UITask::loadSpine()
{
	std::string jsonFile = getParam("jsonFile");
	std::string atlasFile = getParam("atlasFile");
    std::string type = getParam("antType");
	CCLOG("Loading Plist File: %s" , jsonFile.c_str());
	ScoresManager::getInstance().loadSpineData(jsonFile.c_str(),atlasFile.c_str(),(AntType)std::atoi(type.c_str()));
}

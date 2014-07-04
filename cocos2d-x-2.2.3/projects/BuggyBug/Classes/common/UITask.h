#ifndef __UITASK_H__
#define __UITASK_H__

#include "cocos2d.h"
USING_NS_CC;


enum task_type
{
	task_type_plist,
	task_type_xml,
	task_type_image,
    task_type_music,
    task_type_spine
};

class UITask: public CCObject
{
	typedef std::map<std::string,std::string> MapParam;
	typedef MapParam::iterator MapParamIt;
private:
	MapParam			m_params;

	task_type			m_taskType;

	bool findParam(const char *key);

	void deleteParam(const char *key);

	void loadPlist();

	void loadXml();

	void loadImage();
    
    void loadMusic();
    
    void loadSpine();
    
public:
	UITask();
	~UITask();

	static UITask* create(task_type type);
	static UITask* createPlistTask(const char *filePath,const char *texturePath);
	static UITask* createXmlTask(const char *filePath,int type);
	static UITask* createImageTask(const char *filePath);
    static UITask* createMusicTask(const char *filePath ,int type);
    static UITask* createSpineTask(const char *jsonFile, const char *atlasFile, int type);
    

	void init(task_type type);

	void execute();

	void setParams(const char *key,const char *value);

	void setTaskType(task_type type){ this->m_taskType = type; }

	std::string getParam(const char *key);
};

#endif
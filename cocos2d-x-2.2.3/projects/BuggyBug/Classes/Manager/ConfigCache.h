#ifndef __CONFIGCACHE_H__
#define __CONFIGCACHE_H__

#include "cocos2d.h"
#include "UILoaderAchieve.h"
#include "UILoaderTroop.h"
#include "UILoaderAnt.h"
#include "UILoaderLevel.h"
#include "UILoaderItem.h"
USING_NS_CC;

enum config_type
{
	xml_type_achieve,
	xml_type_troop,
    xml_type_ant,
    xml_type_level,
    xml_type_item,
};

enum music_type
{
	music_effect,
	music_bgmusic,
};

enum AntType
{
    tBasicAnt=1,
    tFasterAnt,
    tStrongerFasterAnt,
    tStrongerAnt,
};

enum ItemType
{
    item=1,
    weapon,
    gold,
};

enum AntAttribute
{
    aTotalBlood=1,       //总血
    aCurrentBlood,     //当前血
    aDamage,           //攻击力量，每次攻击打下多少血
    aGoInSpeed,        //默认移动速度
    aComeBackSpeed,    //返回移动速度
    aScore,           //分数
};

#define achieveCache ((UILoaderAchieve*)ConfigCache::sharedConfigCache()->getConfig(xml_type_achieve))
#define troopCache ((UILoaderTroop*)ConfigCache::sharedConfigCache()->getConfig(xml_type_troop))

class UILoader;
class ConfigCache: public CCObject
{
	typedef std::map<config_type,UILoader*> MapLoader;
	typedef MapLoader::iterator MapLoaderIt;
private:
	MapLoader		m_loaderMap;
private:
	ConfigCache(void);
	
public:
	static ConfigCache* sharedConfigCache();
	~ConfigCache(void);

	void addConfigForLoader(UILoader *loader,config_type type);
	void addConfigForFile(const char *filePath,config_type type);
	UILoader* getConfig(config_type type);

	bool init();
};

#endif



#include "ConfigCache.h"

static ConfigCache* pSharedConfigCache = NULL;

ConfigCache::ConfigCache(void)
{
}


ConfigCache::~ConfigCache(void)
{
}

ConfigCache* ConfigCache::sharedConfigCache()
{
	if( !pSharedConfigCache)
	{
		pSharedConfigCache = new ConfigCache;
		pSharedConfigCache->init();
	}
	return pSharedConfigCache;
}

bool ConfigCache::init()
{
	return true;
}

void ConfigCache::addConfigForLoader( UILoader *loader, config_type type )
{
	loader->retain();
	m_loaderMap.insert(std::make_pair(type,loader));
}

void ConfigCache::addConfigForFile( const char *filePath,config_type type )
{
	UILoader *loader = NULL;
	switch(type)
	{
	case xml_type_achieve:
		loader = UILoaderAchieve::create(filePath);
		break;
	case xml_type_troop:
		loader = UILoaderTroop::create(filePath);
		break;
    case xml_type_ant:
        loader = UILoaderAnt::create(filePath);
        break;
    case xml_type_level:
        loader = UILoaderLevel::create(filePath);
        break;
    case xml_type_item:
        loader = UILoaderItem::create(filePath);
        break;
	}
	loader->loadData();
	addConfigForLoader(loader,type);
}

UILoader* ConfigCache::getConfig( config_type type )
{
	MapLoaderIt it = m_loaderMap.find(type);
	return it->second;
}

#include "UILoaderLevel.h"
#include "XmlHandler.h"

UILoaderLevel::UILoaderLevel(void)
{
}

UILoaderLevel::~UILoaderLevel(void)
{
}

UILoaderLevel* UILoaderLevel::create( const char *filename )
{
	UILoaderLevel *loader = new UILoaderLevel;
	loader->initWithFileName(filename);
	loader->autorelease();
	return loader;
}

void UILoaderLevel::parseXml()
{
	Elements elements = m_rootElement->getChildElements("level");
	ElementIt it = elements.begin();
	while( it != elements.end())
	{
		LevelStruct role;
		Element *element = (*it);
		role.id = element->getAttributeInt("id");
		role.name = element->getAttribute("name");
        role.time = element->getAttribute("time");
		Elements childrens = element->getChildElements("property");
		ElementIt childIt = childrens.begin();
		while( childIt != childrens.end())
		{
			Element *child = (*childIt);
			LevelPropertyStruct property;
			property.id = child->getAttributeInt("id");
			property.type = child->getAttribute("type");
			property.ant = child->getAttribute("ant");
            property.describe = child->getAttribute("describe");
			property.number = child->getAttribute("number");
			role.attributes.insert(std::make_pair(property.id,property));
			childIt ++;
			delete child;
		}
		m_attributes.insert(std::make_pair(role.id,role));
		++it;
		delete element;
	}
}

LevelStruct UILoaderLevel::getRole( int key )
{
	MapLevelIt it = m_attributes.find(key);
	return it->second;
}

LevelPropertyStruct UILoaderLevel::getProperty( int roleKey,int proKey )
{
	MapLevelIt it = m_attributes.find(roleKey);
	LevelStruct role = it->second;
	LevelPropertyIt proIt = role.attributes.find(proKey);
	return proIt->second;
}

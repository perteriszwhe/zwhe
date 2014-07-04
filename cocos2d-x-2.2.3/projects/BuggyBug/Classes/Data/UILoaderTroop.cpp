#include "UILoaderTroop.h"
#include "XmlHandler.h"

UILoaderTroop::UILoaderTroop(void)
{
}

UILoaderTroop::~UILoaderTroop(void)
{
}

UILoaderTroop* UILoaderTroop::create( const char *filename )
{
	UILoaderTroop *loader = new UILoaderTroop;
	loader->initWithFileName(filename);
	loader->autorelease();
	return loader;
}

void UILoaderTroop::parseXml()
{
	Elements elements = m_rootElement->getChildElements("role");
	ElementIt it = elements.begin();
	while( it != elements.end())
	{
		RoleStruct role;
		Element *element = (*it);
		role.id = element->getAttributeInt("id");
		role.name = element->getAttribute("name");
		Elements childrens = element->getChildElements("property");
		ElementIt childIt = childrens.begin();
		while( childIt != childrens.end())
		{
			Element *child = (*childIt);
			PropertyStruct property;
			property.id = child->getAttributeInt("id");
			property.key = child->getAttribute("key");
			property.name = child->getAttribute("name");
			property.value = child->getAttribute("value");
			role.attributes.insert(std::make_pair(property.id,property));
			childIt ++;
			delete child;
		}
		childrens = element->getChildElements("desc");
		childIt = childrens.begin();
		std::vector<std::string> descs;
		while( childIt != childrens.end())
		{
			Element *child = (*childIt);
			descs.push_back(child->getContent());
			childIt ++;
			delete child;
		}
		role.descs = descs;
		m_attributes.insert(std::make_pair(role.id,role));
		++it;
		delete element;
	}
}

RoleStruct UILoaderTroop::getRole( int key )
{
	MapRoleIt it = m_attributes.find(key);
	return it->second;
}

PropertyStruct UILoaderTroop::getProperty( int roleKey,int proKey )
{
	MapRoleIt it = m_attributes.find(roleKey);
	RoleStruct role = it->second;
	MapPropertyIt proIt = role.attributes.find(proKey);
	return proIt->second;
}

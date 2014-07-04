#include "UILoaderAnt.h"
#include "XmlHandler.h"

UILoaderAnt::UILoaderAnt(void)
{
}

UILoaderAnt::~UILoaderAnt(void)
{
}

UILoaderAnt* UILoaderAnt::create( const char *filename )
{
	UILoaderAnt *loader = new UILoaderAnt;
	loader->initWithFileName(filename);
	loader->autorelease();
	return loader;
}

void UILoaderAnt::parseXml()
{
	Elements elements = m_rootElement->getChildElements("ant");
	ElementIt it = elements.begin();
	while( it != elements.end())
	{
		AntStruct role;
		Element *element = (*it);
		role.id = element->getAttributeInt("id");
		role.name = element->getAttribute("name");
        role.spineFile = element->getAttribute("spineName");
		Elements childrens = element->getChildElements("property");
		ElementIt childIt = childrens.begin();
		while( childIt != childrens.end())
		{
			Element *child = (*childIt);
			AntPropertyStruct property;
			property.id = child->getAttributeInt("id");
			property.key = child->getAttribute("key");
			property.name = child->getAttribute("name");
			property.value = child->getAttribute("value");
			role.attributes.insert(std::make_pair(property.id,property));
			childIt ++;
			delete child;
		}
//		childrens = element->getChildElements("desc");
//		childIt = childrens.begin();
//		std::vector<std::string> descs;
//		while( childIt != childrens.end())
//		{
//			Element *child = (*childIt);
//			descs.push_back(child->getContent());
//			childIt ++;
//			delete child;
//		}
//		role.descs = descs;
		m_attributes.insert(std::make_pair(role.id,role));
		++it;
		delete element;
	}
}

AntStruct UILoaderAnt::getRole( int key )
{
	MapAntIt it = m_attributes.find(key);
	return it->second;
}

AntPropertyStruct UILoaderAnt::getProperty( int roleKey,int proKey )
{
	MapAntIt it = m_attributes.find(roleKey);
	AntStruct role = it->second;
	AntPropertyIt proIt = role.attributes.find(proKey);
	return proIt->second;
}

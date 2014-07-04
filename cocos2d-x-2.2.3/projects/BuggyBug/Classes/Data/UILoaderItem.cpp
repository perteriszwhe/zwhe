#include "UILoaderItem.h"
#include "XmlHandler.h"

UILoaderItem::UILoaderItem(void)
{
}

UILoaderItem::~UILoaderItem(void)
{
}

UILoaderItem* UILoaderItem::create( const char *filename )
{
	UILoaderItem *loader = new UILoaderItem;
	loader->initWithFileName(filename);
	loader->autorelease();
	return loader;
}

void UILoaderItem::parseXml()
{
	Elements elements = m_rootElement->getChildElements("item");
	ElementIt it = elements.begin();
	while( it != elements.end())
	{
		ItemStruct role;
		Element *element = (*it);
		role.id = element->getAttributeInt("id");
		role.name = element->getAttribute("name");
		Elements childrens = element->getChildElements("property");
		ElementIt childIt = childrens.begin();
		while( childIt != childrens.end())
		{
			Element *child = (*childIt);
			ItemPropertyStruct property;
			property.id = child->getAttributeInt("id");
			property.imageFile = child->getAttribute("imageFile");
            property.playImage = child->getAttribute("playImage");
            property.cdTime = child->getAttributeInt("cdTime");
			property.price = child->getAttribute("price");
            property.type = child->getAttributeInt("type");
            property.describe = child->getAttribute("describe");
			role.attributes.insert(std::make_pair(property.id,property));
			childIt ++;
			delete child;
		}
		m_attributes.insert(std::make_pair(role.id,role));
		++it;
		delete element;
	}
}

ItemStruct UILoaderItem::getRole( int key )
{
	MapItemIt it = m_attributes.find(key);
	return it->second;
}

ItemPropertyStruct UILoaderItem::getProperty( int roleKey,int proKey )
{
	MapItemIt it = m_attributes.find(roleKey);
	ItemStruct role = it->second;
	ItemPropertyIt proIt = role.attributes.find(proKey);
	return proIt->second;
}

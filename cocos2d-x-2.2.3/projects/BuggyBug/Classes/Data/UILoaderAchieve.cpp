#include "UILoaderAchieve.h"
#include "XmlHandler.h"
#include <utility>

UILoaderAchieve::UILoaderAchieve(void)
{
}


UILoaderAchieve::~UILoaderAchieve(void)
{
}

UILoaderAchieve* UILoaderAchieve::create( const char *filename )
{
	UILoaderAchieve *achieve = new UILoaderAchieve;
	achieve->initWithFileName(filename);
	achieve->autorelease();
	return achieve;
}

void UILoaderAchieve::parseXml()
{
	Elements elements = m_rootElement->getChildElements();
	ElementIt it = elements.begin();
	while( it != elements.end())
	{
		Element *element = (*it);
		AchieveStruct achieve;
		achieve.id = element->getAttributeInt("id");
		achieve.key = element->getAttribute("key");
		achieve.value = element->getAttribute("value");
		achieve.progress = element->getAttributeBool("progress");
		achieve.show = element->getAttributeBool("show");
		m_mapAchieve.insert(std::make_pair(achieve.id,achieve));
		delete element;
		++it;
	}
}

AchieveStruct UILoaderAchieve::getAchieve( int key )
{
	MapAchieveIt it = m_mapAchieve.find(key);
	return  it->second;
}

unsigned int UILoaderAchieve::size() const
{
	return m_mapAchieve.size();
}

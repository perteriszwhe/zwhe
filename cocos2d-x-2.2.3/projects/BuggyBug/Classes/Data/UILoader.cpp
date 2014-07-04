#include "UILoader.h"
#include "XmlHandler.h"

UILoader::UILoader(void)
{
}

UILoader::~UILoader(void)
{
	delete m_rootElement;
}

bool UILoader::initWithFileName(const char *filename)
{
	XmlHandler *handler = XmlHandler::create(filename);

	m_rootElement = handler->getRootElelement();

	parseXml();

	return true;
}

void UILoader::loadData()
{

}

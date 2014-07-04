#include "XmlHandler.h"


XmlHandler::XmlHandler(void)
{
}


XmlHandler::~XmlHandler(void)
{
}

XmlHandler* XmlHandler::create( const char *filename )
{
	XmlHandler *handler = new XmlHandler;
	handler->initWithFile(filename);
	handler->autorelease();
	return handler;
}

bool XmlHandler::initWithFile( const char *filename )
{
	std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(filename);
	m_tinyDocument.LoadFile(fullPath.c_str());
	return true;
}

Element* XmlHandler::getRootElelement()
{
	tinyxml2::XMLElement *root = m_tinyDocument.RootElement();
	Element *element = new Element(root);
	return element;
}

Element::Element( tinyxml2::XMLElement *element )
{
	this->m_element = element;
}

Element::~Element()
{
}

std::vector<Element*> Element::getChildElements() const
{
	std::vector<Element*> childElements;
	tinyxml2::XMLElement *firstElement = m_element->FirstChildElement();
	while( NULL != firstElement)
	{
		Element *element = new Element(firstElement);
		childElements.push_back(element);
		firstElement = firstElement->NextSiblingElement();
	}
	return childElements;
}

std::vector<Element*> Element::getChildElements( const char *key ) const
{
	std::vector<Element*> childElements;
	tinyxml2::XMLElement *firstElement = m_element->FirstChildElement();
	while( NULL != firstElement)
	{
		if( 0 == strcmp(firstElement->Name(),key))
		{
			Element *element = new Element(firstElement);
			childElements.push_back(element);
		}
		firstElement = firstElement->NextSiblingElement();
	}
	return childElements;
}

Element* Element::getNextElement() const
{
	tinyxml2::XMLElement *ele = m_element->NextSiblingElement();
	Element* element = new Element(ele);
	return element;
}

Element* Element::getPreviousElement() const
{
	tinyxml2::XMLElement *ele = m_element->PreviousSiblingElement();
	Element *element = new Element(ele);
	return element;
}

const char * Element::getContent() const
{
	const char *content = m_element->GetText();
	return content;
}

const char* Element::getAttribute( const char *key ) const
{
	return m_element->Attribute(key); 
}

int Element::getAttributeInt( const char *key ) const
{
	return m_element->IntAttribute(key);
}

void Element::setAttribute( const char *key, const char *value )
{
	m_element->SetAttribute(key,value);
}

void Element::setAttribute( const char *key,int value )
{
	m_element->SetAttribute(key,value);
}

void Element::setAttribute( const char *key,unsigned int value )
{
	m_element->SetAttribute(key,value);
}

void Element::setAttribute( const char *key,double value )
{
	m_element->SetAttribute(key,value);
}

void Element::setAttribute( const char *key,float value )
{
	m_element->SetAttribute(key,value);
}

unsigned int Element::getAttributeUnsi( const char *key ) const
{
	return m_element->UnsignedAttribute(key);
}

bool Element::getAttributeBool( const char *key ) const
{
	return m_element->BoolAttribute(key);
}

double Element::getAttributeDouble( const char *key ) const
{
	return m_element->DoubleAttribute(key);
}

float Element::getAttributeFloat( const char *key ) const
{
	return m_element->FloatAttribute(key);
}

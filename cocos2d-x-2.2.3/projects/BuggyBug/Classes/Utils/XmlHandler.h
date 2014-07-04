#ifndef __XMLHANDLER_H__
#define __XMLHANDLER_H__

#include "cocos2d.h"
#include "support/tinyxml2/tinyxml2.h"
using namespace cocos2d;

class Element;

typedef std::vector<Element*> Elements;
typedef std::vector<Element*>::iterator ElementIt;

class XmlHandler: public CCObject
{
public:
	XmlHandler(void);
	~XmlHandler(void);

	bool initWithFile(const char *filename);

	static XmlHandler* create(const char *filename);

	Element* getRootElelement();

private:
	tinyxml2::XMLDocument		m_tinyDocument;
};

class Element
{
private:
	tinyxml2::XMLElement		*m_element;

public:
	Element(tinyxml2::XMLElement *element);
	~Element();

	const char* getName() { return m_element->Name(); }

	const char* getAttribute(const char *key) const ;

	int	getAttributeInt(const char *key) const;

	unsigned int getAttributeUnsi(const char *key) const;

	bool getAttributeBool(const char *key) const;

	double getAttributeDouble(const char *key) const;

	float getAttributeFloat(const char *key) const;

	void setAttribute(const char *key, const char *value);

	void setAttribute(const char *key,int value);

	void setAttribute(const char *key,unsigned int value);

	void setAttribute(const char *key,double value);

	void setAttribute(const char *key,float value);

	std::vector<Element*> getChildElements() const;

	std::vector<Element*> getChildElements(const char *key) const;

	Element* getNextElement() const;

	Element* getPreviousElement() const;

	const char *getContent() const;
};

#endif



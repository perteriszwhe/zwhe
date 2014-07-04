#include "UINode.h"
#include "UILayout.h"
#include "UITools.h"

UINode::UINode(void)
	:m_bgSprite(NULL)
{
	this->ignoreAnchorPointForPosition(false);
}


UINode::~UINode(void)
{
}

UINode* UINode::create( const char *bgImg )
{
	CCSprite *sprite = UITools::createSprite(bgImg);
	return UINode::create(sprite);;
}

UINode* UINode::create( CCSprite *bgSprite )
{
	UINode *node = new UINode;
	node->initWithSprite(bgSprite);
	node->autorelease();
	return node;
}

UINode* UINode::create( CCSize &size )
{
	UINode *node = new UINode;
	node->initWithSize(size);
	node->autorelease();
	return node;
}

bool UINode::initWithSize( CCSize &size )
{
	this->setAnchorPoint(ccp(.5,.5));
	this->setContentSize(size);

	return init();
}

void UINode::setBackground( CCSprite *bgSprite )
{
	bgSprite->setPosition(ccp(bgSprite->getContentSize().width * .5,bgSprite->getContentSize().height *.5));
	this->addChild(bgSprite);
	m_bgSprite = bgSprite;
}

bool UINode::initWithFile( const char *bgImg )
{
	CCSprite *sprite = UITools::createSprite(bgImg);
	CCSize size = sprite->getContentSize();
	setBackground(sprite);
	return initWithSize(size);
}

bool UINode::init()
{
	return true;
}

bool UINode::initWithSprite( CCSprite *sprite )
{
	CCSize size = sprite->getContentSize();
	setBackground(sprite);
	return initWithSize(size);
}

void UINode::setLayoutManager( UILayout *layout )
{
	this->addChild(layout);
	layout->setContentSize(this->getContentSize());
}

void UINode::setBackgoundColor( ccColor4B &color )
{
	m_bgSprite->setColor(ccc3(color.r, color.g, color.b));
	m_bgSprite->setOpacity(color.a);
}

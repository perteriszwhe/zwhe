#include "UITouchSprite.h"
#include "UITools.h"

UITouchSprite::UITouchSprite(void)
	:m_isTouchEnabled(false),
	m_clickCallback(NULL),
	m_normalFrame(NULL),
	m_selectFrame(NULL),
	m_isEnabled(true),
	m_nPriority(0)
{
}


UITouchSprite::~UITouchSprite(void)
{
}

bool UITouchSprite::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint localPoint = this->convertTouchToNodeSpace(pTouch);
	CCRect rect = this->boundingBox();
	rect.origin = CCPointZero;
	if( rect.containsPoint(localPoint))
	{
		select();
		return true;
	}
	return false;
}

void UITouchSprite::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher *dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	dispatcher->addTargetedDelegate(this,m_nPriority,true);
}

void UITouchSprite::setTouchEnabled( bool enable )
{
	if( m_isTouchEnabled != enable)
	{
		m_isTouchEnabled = enable;
		if( m_isTouchEnabled)
		{
			registerWithTouchDispatcher();
		}
		else
		{
			CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		}
	}
}

void UITouchSprite::setClickCallback( CCCallFuncN *callback )
{
	if(m_clickCallback != callback)
	{
		CC_SAFE_RELEASE( m_clickCallback);
		callback->retain();
		m_clickCallback = callback;
		m_clickCallback->setTarget(this);
	}
}

UITouchSprite* UITouchSprite::create( const char *img )
{
	UITouchSprite *sprite = new UITouchSprite;
	sprite->initWithSpriteFrameName(img);
	sprite->autorelease();
	return sprite;
}

UITouchSprite* UITouchSprite::create( const char *normalImg,const char *selectImg )
{
	CCSpriteFrame *normalFrame = UITools::createSpriteFrame(normalImg);
	CCSpriteFrame *selectFrame = UITools::createSpriteFrame(selectImg);

	return UITouchSprite::create(normalFrame,selectFrame);	
}

UITouchSprite* UITouchSprite::create( CCSpriteFrame *normalFrame,CCSpriteFrame *selectFrame )
{
	UITouchSprite *sprite = new UITouchSprite;
	sprite->initWithSpriteFrames(normalFrame,selectFrame);
	sprite->autorelease();
	return sprite;
}

bool UITouchSprite::initWithSpriteFrames( CCSpriteFrame *normalFrame,CCSpriteFrame *selectFrame )
{
	if( !CCSprite::initWithSpriteFrame(normalFrame)) return false;
	this->setNormalSpriteFrame(normalFrame);
	this->setSelectSpriteFrame(selectFrame);
	return true;
}

void UITouchSprite::setNormalSpriteFrame( CCSpriteFrame *frame )
{
	if( m_normalFrame)
	{
		m_normalFrame->release();
	}
	m_normalFrame = frame;
	m_normalFrame->retain();
}

void UITouchSprite::setSelectSpriteFrame( CCSpriteFrame *frame )
{
	if( m_selectFrame)
	{
		m_selectFrame->release();
	}
	m_selectFrame = frame;
	m_selectFrame->retain();
}

void UITouchSprite::select()
{
	if( !m_isEnabled) return;
	if( m_selectFrame)
		this->setDisplayFrame(m_selectFrame);
}

void UITouchSprite::unselect()
{
	if( m_normalFrame)
		this->setDisplayFrame(m_normalFrame);
}

void UITouchSprite::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
		unselect();
		CCPoint localPoint = this->convertTouchToNodeSpace(pTouch);
		CCRect rect = this->boundingBox();
		rect.origin = CCPointZero;
		if( rect.containsPoint(localPoint))
		{
			if( m_clickCallback)
				m_clickCallback->execute();
		}
}

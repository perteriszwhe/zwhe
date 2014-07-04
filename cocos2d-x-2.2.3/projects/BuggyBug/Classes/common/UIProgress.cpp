#include "UIProgress.h"
#include "UITools.h"

UIProgress::UIProgress(void)
	:m_bgSprite(NULL),
	m_borderSprite(NULL),
	m_progressSprite(NULL),
	m_progress(NULL),
	m_currentProgress(0)
{
}


UIProgress::~UIProgress(void)
{
}

UIProgress* UIProgress::create( const char *bgImg,const char *borderImg,const char *proImg, bool isZorder)
{
	UIProgress *progress = new UIProgress;
	progress->initWithFile(bgImg,borderImg,proImg,isZorder);
	progress->autorelease();
	return progress;
}

UIProgress* UIProgress::create( const char *borderImg,const char *proImg )
{
	UIProgress *progress = new UIProgress;
	progress->initWithFile(NULL,borderImg,proImg,false);
	progress->autorelease();
	return progress;
}

UIProgress* UIProgress::create( const char *proImg )
{
	UIProgress *progress = new UIProgress;
	progress->initWithFile(NULL,NULL,proImg,false);
	progress->autorelease();
	return progress;
}

bool UIProgress::initWithFile( const char *bgImg,const char *borderImg,const char *proImg, bool isZorder )
{
	CCAssert( proImg,"UIPogress initWithFile (proImg) is NULL" );

	m_progressSprite = UITools::createSprite(proImg);
	m_progress = CCProgressTimer::create(m_progressSprite);
	m_progress->setType(kCCProgressTimerTypeBar);
	m_progress->setMidpoint(ccp(0,0));
	m_progress->setPercentage(m_currentProgress);
	m_progress->setBarChangeRate(ccp(1,0));

	this->setContentSize(m_progressSprite->getContentSize());

	if( bgImg != NULL)
	{
		m_bgSprite = UITools::createSprite(bgImg);
		m_bgSprite->setPosition(getContentSize() / 2);
		this->addChild(m_bgSprite,-1);
	}

	m_progress->setPosition(getContentSize() / 2);
	if( isZorder)
		this->addChild(m_progress,2);
	else
		this->addChild(m_progress,0);

	if( borderImg != NULL )
	{
		m_borderSprite = UITools::createSprite(borderImg);
		m_borderSprite->setPosition(getContentSize() / 2);
		this->addChild(m_borderSprite,1);
	}
	this->setAnchorPoint(ccp(.5,.5));
	return true;
}

void UIProgress::setBorder( const char *img )
{
	if( m_borderSprite )
	{
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(img);
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture,CCRectMake(0,0,texture->getContentSize().width,texture->getContentSize().height));
		m_borderSprite->setDisplayFrame(frame);
	}
}

void UIProgress::setProgressImg( const char *img )
{
	if( m_progressSprite )
	{
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(img);
		CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture,CCRectMake(0,0,texture->getContentSize().width,texture->getContentSize().height));
		m_progressSprite->setDisplayFrame(frame);
	}
}

void UIProgress::setCurrentProgress( float progress )
{
	m_currentProgress = progress;
	m_progress->setPercentage(m_currentProgress);
}

bool UIProgress::isFinish()
{
	return m_currentProgress >= 100;
}

void UIProgress::setColor( ccColor3B &color )
{
	m_borderSprite->setColor(color);
}


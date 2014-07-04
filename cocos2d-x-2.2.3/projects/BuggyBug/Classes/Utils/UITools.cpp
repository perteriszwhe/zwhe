#include "UITools.h"
#include "StringUtils.h"
#include "AllDefines.h"

std::string		UITools::s_fontName = "";
float			UITools::s_fontSize = 12.0f;
ccColor3B		UITools::s_fontColor = ccc3(255,255,255);

std::string		UITools::s_fontNameCurrent = UITools::s_fontName;
float			UITools::s_fontSizeCurrent = UITools::s_fontSize;
ccColor3B		UITools::s_fontColorCurrent = UITools::s_fontColor;

void UITools::initDefaultFont( const char *fontName,float fontSize,ccColor3B &color )
{
	s_fontName = fontName;
	s_fontNameCurrent = fontName;
	s_fontSize = fontSize;
	s_fontSizeCurrent = fontSize;
	s_fontColor = color;
	s_fontColorCurrent = color;
}

void UITools::setFont( const char *fontName,float fontSize, ccColor3B &color )
{
	s_fontNameCurrent = fontName;
	s_fontSizeCurrent = fontSize;
	s_fontColorCurrent = color;
}

void UITools::setFontName(const char *fontName)
{
	s_fontNameCurrent = fontName;
}

void UITools::setFontSize( float fontSize )
{
	s_fontSizeCurrent = fontSize;
}

void UITools::setFontColor( ccColor3B &color )
{
	s_fontColorCurrent = color;
}

CCSprite* UITools::createSpriteButton( const char *bgImg,const char *fontImg )
{
	CCSprite *bgSprite = createSprite(bgImg);
	CCSprite *fontSprite = createSprite(fontImg);
	fontSprite->setPosition(ccp(bgSprite->getContentSize().width * .5,bgSprite->getContentSize().height *.5));
	bgSprite->addChild(fontSprite);
	return bgSprite;
}

CCLabelTTF* UITools::createTestLabel()
{
	CCLabelTTF *label = CCLabelTTF::create("Test","",20); 
	return label;
}

void UITools::removeAllDelegates()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
}

CCTexture2D* UITools::createTexture( const char *key )
{
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(key);
	return texture;
}

CCSprite* UITools::createSprite( const char *spriteImg )
{
	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spriteImg);
	CCSprite *sprite = NULL;
	if( frame != NULL)
	{
		sprite = CCSprite::createWithSpriteFrame(frame);
	}
	else
	{
		sprite = CCSprite::create(spriteImg);
	}
	return sprite;
}

CCSpriteFrame* UITools::createSpriteFrame( const char *frameImg )
{
	CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameImg);
	if( frame == NULL)
	{
		frame = createSpriteFrameFullPath(frameImg);
	}
	return frame;
}

void UITools::replaceScene( CCNode *node )
{
	CCScene *scene = CCScene::create();
	scene->addChild(node);
	CCScene *pScene = CCTransitionFade::create(2.0f,scene);
	CCDirector::sharedDirector()->replaceScene(pScene);
}

CCSprite* UITools::createSpriteFullPath( const char *spriteImg )
{
	CCSprite *sprite = CCSprite::create(spriteImg);
	return sprite;
}

CCSpriteFrame* UITools::createSpriteFrameFullPath( const char *frameImg )
{
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(frameImg);
	CCSpriteFrame *frame = CCSpriteFrame::createWithTexture(texture,CCRectMake(0,0,texture->getContentSize().width,texture->getContentSize().height));
	return frame;
}

void UITools::addMapAnimateToCache( const char *bgImg,const char *whiteImg,const char *grayImg )
{
	if( whiteImg && grayImg && bgImg)
	{
		CCArray *animateArray = CCArray::create();
		CCSpriteFrame *frame1 = UITools::createSpriteFrameFullPath(whiteImg);
		animateArray->addObject(frame1);
		CCSpriteFrame *frame2 = UITools::createSpriteFrameFullPath(grayImg);
		animateArray->addObject(frame2);
		CCSpriteFrame *frame3 = UITools::createSpriteFrameFullPath(bgImg);
		animateArray->addObject(frame3);
		CCAnimation *animation = CCAnimation::createWithSpriteFrames(animateArray,0.15f);
		CCAnimationCache::sharedAnimationCache()->addAnimation(animation,bgImg);
	}
}

void UITools::moveToCenter( CCNode *node )
{
	CCNode *parent = node->getParent();
	if( parent != NULL)
	{
		node->setPosition(parent->getContentSize() / 2);
	}
}

void UITools::setBlendFunc( CCSprite *sprite,int src,int dest )
{
	if( sprite)
	{
		ccBlendFunc blend = {src,dest};
		sprite->setBlendFunc(blend);
	}
}

CCLabelTTF* UITools::createLabelTTF( const char *text )
{
	std::string removeNullStr = StringUtils::removeNull(text);
	CCLabelTTF *label = CCLabelTTF::create(removeNullStr.c_str(),s_fontNameCurrent.c_str(),s_fontSizeCurrent);
	label->setColor(s_fontColor);
	return label;
}

void UITools::restoreFont()
{
	s_fontNameCurrent = s_fontName;
	s_fontSizeCurrent = s_fontSize;
	s_fontColorCurrent = s_fontColor;
}

CCSprite* UITools::createSweetByRand(){
    const char * cakeArra[3];
//    cakeArra[0] = "icecream_100.png";
//    cakeArra[1] = "cake_100.png";
//    cakeArra[2] = "watermelon_100.png";
    cakeArra[0] = "HUD_15.png";
    cakeArra[1] = "HUD_18.png";
    cakeArra[2] = "HUD_21.png";
    int len;
    GET_ARRAY_LEN(cakeArra,len);
    CCSprite* sweetSprite = CCSprite::create(cakeArra[getRandForInt(0, len-1)]);
    return sweetSprite;
}

CCPoint UITools::createAntStartPoint(){
    CCPoint pointArr[4];
    pointArr[0] = ccp(0-20,getRandForInt(0, CCScreenHeight));
    pointArr[1] = ccp(CCScreenWidth+20,getRandForInt(0, CCScreenHeight));
    pointArr[2] = ccp(getRandForInt(0, CCScreenWidth),0-50);
    pointArr[3] = ccp(getRandForInt(0, CCScreenWidth),CCScreenHeight);
    return pointArr[getRandForInt(0, 3)];
}

int UITools::getRandForInt(int start,int end)
{
    cc_timeval psv;
    CCTime::gettimeofdayCocos2d( &psv, NULL );    // 获取本地时间
    //根据时间产生随机种子
    //(这里加上一个rand函数，可解决在循环内(时间间隔极短)取随机数时，
    //连续取得的几个值相同的问题)
    unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
    srand(tsrans);    //设定随机数种子
    float i = CCRANDOM_0_1()*(end-start+1)+start;  //产生一个从start到end间的随机数
    return (int)i;
}

float UITools::getRandForFloat(float start,float end)
{
    cc_timeval psv;
    CCTime::gettimeofdayCocos2d( &psv, NULL );    // 获取本地时间
    //根据时间产生随机种子
    //(这里加上一个rand函数，可解决在循环内(时间间隔极短)取随机数时，
    //连续取得的几个值相同的问题)
    unsigned int tsrans = psv.tv_sec * 1000 + psv.tv_usec / 1000 + rand();
    srand(tsrans);    //设定随机数种子
    return CCRANDOM_0_1()*(end-start+0.1)+start;
}






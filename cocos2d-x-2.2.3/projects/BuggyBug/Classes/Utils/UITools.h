#ifndef __UITOOLS_H__
#define __UITOOLS_H__

#include "cocos2d.h"
#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}
enum sweet_type
{
	sweet_type_cake,
	sweet_type_icecream,
	sweet_type_watermelon
};

using namespace cocos2d;

class UITools: public CCObject
{
private:
	static std::string	s_fontName;
	static float		s_fontSize;
	static ccColor3B	s_fontColor;

	static std::string	s_fontNameCurrent;
	static float		s_fontSizeCurrent;
	static ccColor3B	s_fontColorCurrent;

public:

	static void initDefaultFont(const char *fontName,float fontSize,ccColor3B &color);

	static void setFont(const char *fontName,float fontSize, ccColor3B &color);

	static void setFontName(const char *fontName);

	static void setFontSize(float fontSize);

	static void setFontColor(ccColor3B &color);

	static void restoreFont();

	static CCSprite* createSpriteButton(const char *bgImg,const char *fontImg);

	static CCLabelTTF* createTestLabel();

	static void removeAllDelegates();

	static CCTexture2D* createTexture(const char *key);

	static CCSprite* createSprite(const char *spriteImg);

	static CCSprite* createSpriteFullPath(const char *spriteImg);

	static CCSpriteFrame* createSpriteFrame(const char *frameImg);

	static CCSpriteFrame* createSpriteFrameFullPath(const char *frameImg);

	static void replaceScene(CCNode *node);

	static void addMapAnimateToCache( const char *bgImg,const char *whiteImg,const char *grayImg);

	static void moveToCenter(CCNode *node);

	static void setBlendFunc(CCSprite *sprite,int src,int dest);

	static CCLabelTTF* createLabelTTF(const char *text);
    
    //随机获取糖果
    static CCSprite* createSweetByRand();
    //随机获取一个靠边的坐标
    static CCPoint createAntStartPoint();
    //获取随机整数
    static int getRandForInt(int start,int end);
    //获取随机小数
    static float getRandForFloat(float start,float end);

};

#endif



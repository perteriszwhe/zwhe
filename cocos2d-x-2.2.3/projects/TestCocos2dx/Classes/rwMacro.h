#ifndef  _RWMACRO_H_
#define  _RWMACRO_H_


#include <stdio.h>

#define  CCScreenWidth CCDirector::sharedDirector()->getWinSize().width
#define  CCScreenHeight CCDirector::sharedDirector()->getWinSize().height

#define  CCPointCenter ccp(CCScreenWidth /2 , CCScreenHeight /2 )
#define  CCPointCenterTop ccp(CCScreenWidth /2 ,CCScreenHeight)
#define  CCPointCenterBottom ccp(CCScreenWidth /2 ,0)

#define  CCPointRightTop  ccp(CCScreenWidth ,CCScreenHeight )

#define CCSizeWidth(sprite) sprite->getContentSize().width 
#define CCSizeHeight(sprite) sprite->getContentSize().height 

#define  CCPointRightTopWithNode(sprite) ccp(CCScreenWidth - sprite->getContentSize().width/2 ,\
	CCScreenHeight - sprite->getContentSize().height/2)
#define  CCEaseInOutMove(time , pos) CCEaseSineInOut::actionWithAction(CCMoveTo::actionWithDuration(time, pos )) 




#endif
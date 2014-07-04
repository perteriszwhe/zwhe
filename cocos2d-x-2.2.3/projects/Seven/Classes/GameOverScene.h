//
//  GameOverScene.h
//  Seven
//
//  Created by He Zhiwei on 14-4-16.
//
//

#ifndef __Seven__GameOverScene__
#define __Seven__GameOverScene__

#include "cocos2d.h"
USING_NS_CC;

class GameOverScene : public CCLayerColor
{
public:
	virtual bool init();
    std::string numStr;
    int numOne;
    int numTwo;
    CCLabelTTF* pLabel;
    static CCScene* scene();
    void myupdate();
    
    CREATE_FUNC(GameOverScene);
};

#endif /* defined(__Seven__GameOverScene__) */

//
//  ShopwindowCell.h
//  BuggyBug
//
//  Created by He Zhiwei on 14-5-18.
//
//

#ifndef __BuggyBug__ShopwindowCell__
#define __BuggyBug__ShopwindowCell__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ShopwindowCell:public CCTableViewCell
{
public:
    virtual void onEnter();
    virtual void onExit();
    void draw();
};

#endif /* defined(__BuggyBug__ShopwindowCell__) */

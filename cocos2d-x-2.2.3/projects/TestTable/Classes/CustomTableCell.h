//
//  CustomTableCell.h
//  TestTable
//
//  Created by He Zhiwei on 14-5-18.
//
//

#ifndef __TestTable__CustomTableCell__
#define __TestTable__CustomTableCell__

#include "cocos-ext.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CustomTableCell:public cocos2d::extension::CCTableViewCell
{
public:
    void draw();
};

#endif /* defined(__TestTable__CustomTableCell__) */

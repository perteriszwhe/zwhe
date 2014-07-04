#include "HelloWorldScene.h"
#include "CustomTableCell.h"

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    
    CCTableView *tableview = CCTableView::create(this, CCSizeMake(442, 228));
    tableview->setDirection(kCCScrollViewDirectionVertical); //设置tableview的方向是竖直方向，当然也有水平方向
    tableview->setDelegate(this);
    tableview->setVerticalFillOrder(kCCTableViewFillTopDown);// 设置tableview cell的index排列，这里设置是从上到下变大，当然也可以从下到上变大。
    tableview->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
    this->addChild(tableview);
    
    return true;
}

void HelloWorld::tableCellTouched(cocos2d::extension::CCTableView *table, cocos2d::extension::CCTableViewCell *cell)
{
    CCLOG("you touch cell index = %u",cell->getIdx());
}

CCSize HelloWorld::tableCellSizeForIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    return CCSizeMake(442, 114);
}

unsigned int HelloWorld::numberOfCellsInTableView(cocos2d::extension::CCTableView *table)
{
    return 10;
}

CCTableViewCell* HelloWorld::tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx)
{
    CCString *string = CCString::createWithFormat("index = %d",idx);
    CCTableViewCell *cell = table->dequeueCell();
    if (!cell) {
        cell = new CustomTableCell();
        cell->autorelease();
        
        //添加背景图片
        CCSprite *sprite = CCSprite::create("111.png");
        sprite->setAnchorPoint(CCPointZero);
        sprite->setPosition(ccp(0, 0));
        cell->addChild(sprite,1);
        
        CCSprite *sprite1 = CCSprite::create("item1.png");
        sprite1->setAnchorPoint(CCPointZero);
        sprite1->setPosition(ccp(45, 0));
        cell->addChild(sprite1,1);
        
        //添加背景图片
        CCSprite *sprite2 = CCSprite::create("item2.png");
        sprite2->setAnchorPoint(CCPointZero);
        sprite2->setPosition(ccp(140, 0));
        cell->addChild(sprite2,1);
        
        //添加背景图片
        CCSprite *sprite3 = CCSprite::create("item3.png");
        sprite3->setAnchorPoint(CCPointZero);
        sprite3->setPosition(ccp(240, 0));
        cell->addChild(sprite3,1);
        
        //添加背景图片
        CCSprite *sprite4 = CCSprite::create("item4.png");
        sprite4->setAnchorPoint(CCPointZero);
        sprite4->setPosition(ccp(330, 0));
        cell->addChild(sprite4,1);
        
        //添加label
        CCLabelTTF *label = CCLabelTTF::create(string->getCString(), "Arial", 15);
        label->setAnchorPoint(CCPointZero);
        label->setTag(123);
        label->cocos2d::CCNode::setPosition(5, 5);
        cell->addChild(label,2);
        
//        //添加menu
//        CCMenuItemImage *itemImage1 = CCMenuItemImage::create("Icon-72.png", "Icon-72.png", cell, menu_selector(HelloWorld::menuCallBack));
//        CCMenuItemImage *itemImage2 = CCMenuItemImage::create("Icon-72.png", "Icon-72.png", cell, menu_selector(HelloWorld::menuCallBack));
//        CCMenuItemImage *itemImage3 = CCMenuItemImage::create("Icon-72.png", "Icon-72.png", cell, menu_selector(HelloWorld::menuCallBack));
//        CCMenuItemImage *itemImage4 = CCMenuItemImage::create("Icon-72.png", "Icon-72.png", cell, menu_selector(HelloWorld::menuCallBack));
//        CCMenu *menu = CCMenu::create(itemImage1,itemImage2,itemImage3,itemImage4,NULL);
//        
//        //注意CCMenu是无法修改锚点的，其默认位置是在其几何中心
//        menu->setPosition(ccp(180,26));
//        menu->alignItemsHorizontally();
//        
//        //可以通过修改CCMenuItemImage的锚点的位置
//        //        itemImage->setAnchorPoint(CCPointZero);
//        //        menu->setPosition(ccp(180,6));
//        
//        cell->addChild(menu, 2);
//        
//        CCSprite *sprite = CCSprite::create("item1.png");
//        sprite->setAnchorPoint(CCPointZero);
//        sprite->setPosition(ccp(0, 0));
//        cell->addChild(sprite,1);
    }
    
    else
    {
        //由于每一个cell的label都是不同的，所以我们通过tag值获取到label来对label进行修改
        CCLabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(string->getCString());
    }
    
    return cell;
}

void HelloWorld::menuCallBack(cocos2d::CCObject *pSender)
{
    CCTableViewCell *cell = (CCTableViewCell*)(((CCMenuItemImage*)pSender)->getParent()->getParent());
    CCLog("menu click cell index : %d",cell->getIdx());
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}

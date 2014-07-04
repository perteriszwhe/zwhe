//
//  ItemSlot.cpp
//  BuggyBug
//
//  Created by He Zhiwei on 14-6-4.
//
//

#include "ItemSlot.h"
#include "AllDefines.h"
#include "UITools.h"
#include "DBUtil.h"
#include "GamePlayScene.h"
ItemSlot* ItemSlot::createWithType(SlotIndex sloteIndex){
    ItemSlot * node = ItemSlot::createWithFile("skeleton.json", "skeleton.atlas");
    node->setSlotIndex(sloteIndex);
    return node;
}

void ItemSlot::setSlotIndex(SlotIndex sloteIndex){
    m_slotIndex = sloteIndex;
}

ItemSlot* ItemSlot::createWithFile (const char* skeletonDataFile, const char* atlasFile, float scale) {
	ItemSlot* node = new ItemSlot(skeletonDataFile, atlasFile, scale);
	node->autorelease();
	return node;
}

ItemSlot::ItemSlot (const char* skeletonDataFile, const char* atlasFile, float scale)
: CCSkeletonAnimation(skeletonDataFile, atlasFile, scale) {
	addAnimationState();
}

ItemSlot* ItemSlot::createWithData (SkeletonData* skeletonData) {
	ItemSlot* node = new ItemSlot(skeletonData);
	node->autorelease();
	return node;
}

ItemSlot::ItemSlot (SkeletonData *skeletonData)
: CCSkeletonAnimation(skeletonData) {
	addAnimationState();
}

ItemSlot::~ItemSlot(){
    
}

void ItemSlot::onEnterTransitionDidFinish()
{
    
}

void ItemSlot::initSelf(){
    switch (m_slotIndex) {
        case sloteOne:
            this->setPosition(ccp(CCScreenWidth*0.05, CCScreenHeight*0.01));
            break;
        case sloteTwo:
            this->setPosition(ccp(CCScreenWidth*0.14, CCScreenHeight*0.01));
            break;
        case sloteThree:
            this->setPosition(ccp(CCScreenWidth*0.05, CCScreenHeight*0.17));
            break;
        case sloteFour:
            this->setPosition(ccp(CCScreenWidth*0.23, CCScreenHeight*0.01));
            break;
        case sloteFive:
            this->setPosition(ccp(CCScreenWidth*0.05, CCScreenHeight*0.33));
            break;
        default:
            break;
    }
    
    this->setAnimation("ready", false,0);
    //skeletonNode5->setAnimation("active", true,0);
    this->setSkin("default");
    this->setScale(0.5);
    
    mProgressTimer = CCProgressTimer::create(CCSprite::create("shadow-full.png"));
    mProgressTimer->setPosition(ccp(-3,130));
    //设置进度条的样式
    mProgressTimer->setType(kCCProgressTimerTypeRadial);
    //设置进度条的值的范围【0 100】
    mProgressTimer->setPercentage(100);
    mProgressTimer->setScale(1.8);
    mProgressTimer->setVisible(false);
    
    //反进度计时
    mProgressTimer->setReverseProgress(true);
    addChild(mProgressTimer);
}

void ItemSlot::startCD()
{
    this->setAnimation("ready", false,0);
    mProgressTimer->setVisible(true);
    setTouchEnabled(false);
    //设置动作
    CCActionInterval* action_progress_from_to = CCProgressFromTo::create(m_itemInfo.cdTime, 100, 0);
    CCCallFunc* action_callback = CCCallFuncN::create(this, callfuncN_selector(ItemSlot::skillCoolDownCallBack));
    mProgressTimer->runAction(CCSequence::create(action_progress_from_to, action_callback, NULL));
    
    cdTimeLabel = CCLabelTTF::create(CCString::createWithFormat("%d",m_itemInfo.cdTime)->getCString(), "AmericanTypewriter-Bold", 50);
    cdTimeLabel->setPosition(ccp(0, 125));
    addChild(cdTimeLabel,100);
    
    schedule(schedule_selector(ItemSlot::cdTimeAction),1.0);
}

void ItemSlot::cdTimeAction()
{
    int cdTime = std::atoi(cdTimeLabel->getString());
    if (cdTime-1>0) {
        cdTimeLabel->setString(CCString::createWithFormat("%d",cdTime-1)->getCString());
    }else{
        this->unschedule(schedule_selector(ItemSlot::cdTimeAction));
        cdTimeLabel->removeFromParent();
    }
}

/** 技能冷却完成回调 */
void ItemSlot::skillCoolDownCallBack(CCNode* node)
{
    // 进度条技能不可见
    mProgressTimer->setVisible(false);
    // 按钮置为可用
    this->setTouchEnabled(true);
    this->setAnimation("active", true,0);
}

void ItemSlot::onEnter()
{
    CCNode::onEnter();
    setTouchEnabled(true);
    this->initSelf();
}

void ItemSlot::onExit()
{
    CCNode::onExit();
    setTouchEnabled(false);
}

void ItemSlot::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher *dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	dispatcher->addTargetedDelegate(this,m_nPriority,true);
}

void ItemSlot::setTouchEnabled( bool enable )
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

bool ItemSlot::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    if (!isTouchMe(pTouch))
	{
		return false;
	}
	CCLOG("点击了！！！！");
	return true;
}

void ItemSlot::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent ){
    
}

//判断是否点击到蚂蚁
bool ItemSlot::isTouchMe( CCTouch* pTouch )
{
    //获得点击的OpenGL的世界坐标值
    CCPoint touchPoint = pTouch->getLocation();
    //将点击的位置转换成父元素坐标系中的相对坐标
    CCPoint pt=getParent()->convertToNodeSpace(touchPoint);
    CCLOG("点击的坐标X：%f  Y:%f",pt.x,pt.y);
    //得到自己在父元素坐标系中的位置范围
    CCRect rect=boundingBox();
    if(pt.x >= rect.origin.x && pt.x <= rect.origin.x+rect.size.width
       && pt.y >= rect.origin.y && pt.y <= rect.origin.y+rect.size.width)
    {
        if (m_itemInfo.number-1>0) {
            m_itemInfo.number = m_itemInfo.number-1;
            DBUtil::initDB("MyGameInfo.db");
            std::string updateNumberSql = "update my_item set number = "+CCString::createWithFormat("%d",m_itemInfo.number)->m_sString+" where itemid = "+CCString::createWithFormat("%d",m_itemInfo.id)->m_sString+" and type = "+CCString::createWithFormat("%d",m_itemInfo.type)->m_sString+";";
            DBUtil::updateData(updateNumberSql);
            DBUtil::closeDB();
            numberLabel->setString(CCString::createWithFormat("%d",m_itemInfo.number)->getCString());
            GamePlayScene *node = (GamePlayScene*)this->getParent()->getParent();
            node->m_itemInfo = m_itemInfo;
            this->startCD();
        }else if(m_itemInfo.number-1==0){
            m_itemInfo.number = 0;
            DBUtil::initDB("MyGameInfo.db");
            std::string deleteSql = "delete from my_item where itemid = "+CCString::createWithFormat("%d",m_itemInfo.id)->m_sString+" and type = "+CCString::createWithFormat("%d",m_itemInfo.type)->m_sString+";";
            DBUtil::deleteData(deleteSql);
            DBUtil::closeDB();
            numberLabel->setString(CCString::createWithFormat("%d",0)->getCString());
            this->startCD();
            this->setTouchEnabled(false);
        }
        
        
        
        
        return true;
    }else{
        return false;
    }
}

void ItemSlot::equipItem(ItemPropertyStruct itemInfo)
{
    if (itemInfo.id) {
        m_itemInfo = itemInfo;
    }
    itemSprite = UITools::createSprite(m_itemInfo.playImage.c_str());
    itemSprite->setScale(1.8);
    itemSprite->setPosition(ccp(-3,130));
    addChild(itemSprite);
    
    //numberLabel->setString(CCString::createWithFormat("%d",m_itemInfo.number)->getCString());
    numberLabel = CCLabelTTF::create(CCString::createWithFormat("%d",m_itemInfo.number)->getCString(), "", 38);
    numberLabel->setPosition(ccp(0,40));
    addChild(numberLabel);
}
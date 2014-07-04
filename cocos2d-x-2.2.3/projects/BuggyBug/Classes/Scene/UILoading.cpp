#include "UILoading.h"
#include "UINode.h"
#include "UIProgress.h"
#include "UITaskManager.h"
#include "UITask.h"
#include "ConfigCache.h"
#include "UITools.h"
#include "ScoresManager.h"
#include "GameMianScene.h"

CCScene* UILoading::scene()
{
	CCScene *scene = CCScene::create();
	if( scene)
	{
		CCLayer *layer = UILoading::create();
		scene->addChild(layer);
		return scene;
	}
	return NULL;
}

UILoading::UILoading(void)
{
}


UILoading::~UILoading(void)
{
	CC_SAFE_RELEASE( m_taskManager);
}

bool UILoading::init()
{
	if( !CCLayer::init()) return false;

	m_taskManager = UITaskManager::create(CCCallFuncN::create(this,callfuncN_selector(UILoading::taskAllFinishCallback)));
	m_taskManager->setTaskEndCallback(CCCallFuncN::create(this,callfuncN_selector(UILoading::onTaskEndCallback)));
	this->addChild(m_taskManager);
	
	m_progress = UIProgress::create("battle_ui_timebar_b.png","battle_ui_timebar_mask.png","battle_ui_timebar_f.png");
	m_progress->setScaleX(.4f);
	m_progress->setPosition(getContentSize() / 2);
	this->addChild(m_progress);

	m_titleLabel = CCLabelTTF::create("Loading scene ...","",16);
	m_titleLabel->setAnchorPoint(ccp(0,0.5));
	m_titleLabel->setPosition(getContentSize() / 2 + ccp(-120,30));
	this->addChild(m_titleLabel);

	loadResource();
    //加载骨骼动画文件
    //ScoresManager::getInstance().loadSpineData();
    

	return true;
}

void UILoading::update( float delta )
{
}

void UILoading::loadResource()
{
	m_taskManager->addXml("achieve.xml",xml_type_achieve);
	//m_taskManager->addXml("troop.xml",xml_type_troop);
    m_taskManager->addXml("ant.xml",xml_type_ant);
    m_taskManager->addXml("level.xml",xml_type_level);
    m_taskManager->addXml("item.xml",xml_type_item);
    
    m_taskManager->addSpine("basic-ant.json", "basic-ant.atlas", tBasicAnt);
	m_taskManager->addSpine("faster-ant.json", "faster-ant.atlas", tFasterAnt);
    m_taskManager->addSpine("stronger-and-faster-ant.json", "stronger-and-faster-ant.atlas", tStrongerFasterAnt);
    m_taskManager->addSpine("stronger-ant.json", "stronger-ant.atlas", tStrongerAnt);
    
    m_taskManager->addMusic("homebg2.mp3", music_bgmusic);
    m_taskManager->addMusic("gamebg2.mp3", music_bgmusic);
    m_taskManager->addMusic("gamebg3.mp3", music_bgmusic);
    m_taskManager->addMusic("fullhealth_music.mp3", music_bgmusic);
    m_taskManager->addMusic("twoxuebg.mp3", music_bgmusic);
    m_taskManager->addMusic("dead.mp3", music_bgmusic);
    m_taskManager->addMusic("storebg.mp3", music_bgmusic);
    
    m_taskManager->addMusic("hit.wav", music_effect);
    m_taskManager->addMusic("miss.wav", music_effect);
    m_taskManager->addMusic("ArmourShop.wav", music_effect);
    m_taskManager->addMusic("CoinI.wav", music_effect);
    m_taskManager->addMusic("NotthefinalANTTAP.wav", music_effect);
    m_taskManager->addMusic("WeaponShop.wav", music_effect);
    m_taskManager->addMusic("Welcometotheshop.wav", music_effect);
    m_taskManager->addMusic("button.mp3", music_effect);

	m_taskManager->doTask();
}

void UILoading::taskAllFinishCallback(CCNode *node)
{
	CCTransitionMoveInT* transition = CCTransitionMoveInT ::create(0.5f,GameMianScene::scene());
    CCDirector::sharedDirector()->replaceScene(transition);
}

void UILoading::onTaskEndCallback( CCNode *node )
{
	std::string title = "Loading: ";
	UITask *task = m_taskManager->getCurrentTask();
	std::string filePath = task->getParam("filePath");
	if( filePath.length() > 17)
	{
		filePath = filePath.substr(0,17);
		filePath.append("...");
	}
	title.append(filePath);
	m_titleLabel->setString(title.c_str());
	float progress = m_taskManager->getProgress();
	m_progress->setCurrentProgress(progress);
}


//
//  ScoresManager.h
//  TestCocos2dx
//
//  Created by He Zhiwei on 14-4-22.
//
//

#ifndef __TestCocos2dx__ScoresManager__
#define __TestCocos2dx__ScoresManager__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCSkeletonAnimation.h"
#include "structDef.h"
#include "ConfigCache.h"
USING_NS_CC;
USING_NS_CC_EXT;

class ScoresManager{
    typedef std::map<AntType,SkeletonData*> SpineLoader;
	typedef SpineLoader::iterator SpineLoaderIt;
public:
    int cakeScores = 10;
    int myScores;
    
    int boCi = 1;
    int antNum = 0;
    int sAntNum = 0;
    float gameTime = 20.0f;
    SpineLoader m_LoaderSpine;
public:
    static ScoresManager& getInstance(){
        static ScoresManager instance;
        return instance;
    }
    
    int addMyScores(int score);
    int getMyTotalScores();
    int subCakeScores(int score);
    int getCakeTotalScores();
    void resetScores();
    
    void selectBoci(int boCiNum);
    void resetBoci();
    void loadSpineData(const char *jsonFile, const char *atlasFile, AntType type);
    SkeletonData* getSpineData(AntType antType);
    AntInfo getAntInfoForType(AntType antType);
};

#endif /* defined(__TestCocos2dx__ScoresManager__) */

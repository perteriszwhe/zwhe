//
//  ScoresManager.cpp
//  TestCocos2dx
//
//  Created by He Zhiwei on 14-4-22.
//
//

#include "ScoresManager.h"

int ScoresManager::addMyScores(int score)
{
    return myScores = myScores+score;
}

int ScoresManager::getMyTotalScores()
{
    return myScores;
}

int ScoresManager::subCakeScores(int score)
{
    return cakeScores = cakeScores-score;
}

int ScoresManager::getCakeTotalScores()
{
    return cakeScores;
}

void ScoresManager::resetScores()
{
    myScores = 0;
    cakeScores = 10;
}

void ScoresManager::selectBoci(int boCiNum)
{
    switch (boCiNum) {
        case 1:
            boCi = boCiNum;
            antNum =60;
            sAntNum = 0;
            gameTime = 30.0f;
            break;
        case 2:
            boCi = boCiNum;
            antNum =60;
            sAntNum = 10;
            gameTime = 30.0f;
            break;
        case 3:
            boCi = boCiNum;
            antNum =65;
            sAntNum = 15;
            gameTime = 30.0f;
            break;
        case 4:
            boCi = boCiNum;
            antNum =120;
            sAntNum = 30;
            gameTime = 60.0f;
            break;
        case 5:
            boCi = boCiNum;
            antNum =800;
            sAntNum = 60;
            gameTime = 60.0f;
            break;
        case 6:
            boCi = boCiNum;
            antNum =1000;
            sAntNum = 70;
            gameTime = 60.0f;
            break;
        case 7:
            boCi = boCiNum;
            antNum =1200;
            sAntNum = 80;
            gameTime = 60.0f;
            break;
        case 8:
            boCi = boCiNum;
            antNum =1200;
            sAntNum = 90;
            gameTime = 60.0f;
            break;
        case 9:
            boCi = boCiNum;
            antNum =1200;
            sAntNum = 100;
            gameTime = 60.0f;
            break;
        case 10:
            boCi = boCiNum;
            antNum =2000;
            sAntNum = 100;
            gameTime = 60.0f;
            break;
            
        default:
            break;
    }
}

void ScoresManager::resetBoci()
{
    antNum = 0;
    sAntNum = 0;
    gameTime = 0.0f;
}

void ScoresManager::loadSpineData(const char *jsonFile, const char *atlasFile, AntType type)
{
//    Atlas *a = Atlas_readAtlasFile("stronger-ant.atlas");
//    SkeletonJson *j = SkeletonJson_create(a);
//    SkeletonData *d = SkeletonJson_readSkeletonDataFile(j,"stronger-ant.json");
    
    SkeletonData * ant_skData = SkeletonJson_readSkeletonDataFile(SkeletonJson_create(Atlas_readAtlasFile(atlasFile)),jsonFile);
    m_LoaderSpine.insert(std::map<AntType,SkeletonData*>::value_type(type, ant_skData));
}

SkeletonData* ScoresManager::getSpineData(AntType antType)
{
    SpineLoaderIt it = m_LoaderSpine.find(antType);
	return it->second;
}

AntInfo ScoresManager::getAntInfoForType(AntType antType)
{
    AntInfo antInfo;
    switch (antType) {
        case tBasicAnt:
            antInfo.totalBlood = 1;
            antInfo.currentBlood = 1;
            antInfo.damage = 1;
            antInfo.goInSpeed = 40;
            antInfo.comeBackSpeed = 130;
            break;
        case tFasterAnt:
            antInfo.totalBlood = 1;
            antInfo.currentBlood = 1;
            antInfo.damage = 1;
            antInfo.goInSpeed = 80;
            antInfo.comeBackSpeed = 130;
            break;
        case tStrongerFasterAnt:
            antInfo.totalBlood = 2;
            antInfo.currentBlood = 2;
            antInfo.damage = 2;
            antInfo.goInSpeed = 40;
            antInfo.comeBackSpeed = 130;
            break;
        default:
            break;
    }
    return antInfo;
}


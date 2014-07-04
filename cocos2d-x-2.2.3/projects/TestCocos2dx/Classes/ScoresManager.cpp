//
//  ScoresManager.cpp
//  TestCocos2dx
//
//  Created by He Zhiwei on 14-4-22.
//
//

#include "ScoresManager.h"

int ScoresManager::addMyScores(int score){
    return myScores = myScores+score;
}

int ScoresManager::getMyTotalScores(){
    return myScores;
}

int ScoresManager::subCakeScores(int score){
    return cakeScores = cakeScores-score;
}

int ScoresManager::getCakeTotalScores(){
    return cakeScores;
}

void ScoresManager::resetScores(){
    myScores = 0;
    cakeScores = 10;
}

void ScoresManager::selectBoci(int boCiNum){
    switch (boCiNum) {
        case 1:
            boCi = boCiNum;
            antNum =90;
            sAntNum = 0;
            gameTime = 30.0f;
            break;
        case 2:
            boCi = boCiNum;
            antNum =280;
            sAntNum = 30;
            gameTime = 60.0f;
            break;
        case 3:
            boCi = boCiNum;
            antNum =390;
            sAntNum = 40;
            gameTime = 60.0f;
            break;
        case 4:
            boCi = boCiNum;
            antNum =600;
            sAntNum = 50;
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

void ScoresManager::resetBoci(){
    antNum = 0;
    sAntNum = 0;
    gameTime = 0.0f;
}
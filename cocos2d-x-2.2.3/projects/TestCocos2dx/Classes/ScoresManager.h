//
//  ScoresManager.h
//  TestCocos2dx
//
//  Created by He Zhiwei on 14-4-22.
//
//

#ifndef __TestCocos2dx__ScoresManager__
#define __TestCocos2dx__ScoresManager__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class ScoresManager{
public:
    int cakeScores = 10;
    int myScores;
    
    int boCi = 1;
    int antNum = 0;
    int sAntNum = 0;
    float gameTime = 20.0f;
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
};

#endif /* defined(__TestCocos2dx__ScoresManager__) */

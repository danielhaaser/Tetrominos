//
//  GameScene.h
//  Tetrominos
//
//  Created by Daniel Haaser on 7/1/15.
//
//

#ifndef __Tetrominos__GameScene__
#define __Tetrominos__GameScene__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "TetrominoBag.h"

class Coordinate;
class Grid;
class Tetromino;

class GameScene : public cocos2d::Node
{
public:
    CREATE_FUNC(GameScene);
    
protected:
    Grid* grid;
    std::unique_ptr<TetrominoBag> tetrominoBag;
    bool active;
    cocos2d::ui::Text* scoreLabel;
    cocos2d::ui::Text* timeLeftLabel;
    int totalScore;
    float stepInterval;
    float timeLeft;
    
    // Lifecycle
    bool init() override;
    void onEnter() override;
    void setupTouchHandling();
    
    // Game Logic
    Tetromino* createRandomTetromino();
    void setGameActive(bool active);
    void step(float dt);
    void update(float dt) override;
    void updateStateFromScore();
    void updateGameSpeed(int score);
    void gameOver();
    void setTimeLeft(float time);
    
    // Utility
    Coordinate convertPositionToCoordinate(cocos2d::Vec2 position);
    
    // UI
    void backButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void updateScoreLabel(int score);
    
};

#endif /* defined(__Tetrominos__GameScene__) */

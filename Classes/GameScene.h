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

class Grid;

class GameScene : public cocos2d::Node
{
public:
    CREATE_FUNC(GameScene);
    
protected:
    Grid* grid;
    
    bool init() override;
    void onEnter() override;
    void backButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
};

#endif /* defined(__Tetrominos__GameScene__) */

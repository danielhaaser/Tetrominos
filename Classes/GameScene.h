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

class GameScene : cocos2d::Node
{
public:
    CREATE_FUNC(GameScene);
    
protected:
    bool init() override;
};

#endif /* defined(__Tetrominos__GameScene__) */

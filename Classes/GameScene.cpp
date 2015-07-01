//
//  GameScene.cpp
//  Tetrominos
//
//  Created by Daniel Haaser on 7/1/15.
//
//

#include "GameScene.h"

using namespace cocos2d;

bool GameScene::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    LayerColor* background = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(background);
    
    return true;
}
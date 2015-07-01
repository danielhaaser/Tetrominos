//
//  GameScene.cpp
//  Tetrominos
//
//  Created by Daniel Haaser on 7/1/15.
//
//

#include "GameScene.h"
#include "SceneManager.h"
#include "Grid.h"

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

void GameScene::onEnter()
{
    Node::onEnter();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // setup grid
    grid = Grid::create();
    grid->setAnchorPoint(Vec2(0.5f, 0.0f));
    grid->setPosition(Vec2(visibleSize.width * 0.5f, 0.0f));
    this->addChild(grid);
    
    // setup menus
    ui::Button* backButton = ui::Button::create();
    backButton->setAnchorPoint(Vec2(0.0f, 1.0f));
    backButton->setPosition(Vec2(0.0f, visibleSize.height));
    backButton->loadTextures("backButton.png", "backButtonPressed.png");
    backButton->addTouchEventListener(CC_CALLBACK_2(GameScene::backButtonPressed, this));
    this->addChild(backButton);
}

void GameScene::backButtonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        SceneManager::getInstance()->returnToLobby();
    }
}
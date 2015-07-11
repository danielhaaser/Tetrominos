//
//  Lobby.cpp
//  Tetrominos
//
//  Created by Daniel Haaser on 7/1/15.
//
//

#include "Lobby.h"
#include "CocosGUI.h"
#include "SceneManager.h"

using namespace cocos2d;

bool Lobby::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    LayerColor* background = LayerColor::create(Color4B(255, 255, 255, 255));
    
    this->addChild(background);
    
    return true;
}

void Lobby::onEnter()
{
    Node::onEnter();
    
    SceneManager::getInstance()->receiveMultiplayerInvitations();
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite* logo = Sprite::create("logo.png");
    logo->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.7f));
    
    ui::Button* singlePlayerButton = ui::Button::create();
    ui::Button* multiplayerButton = ui::Button::create();
    
    singlePlayerButton->loadTextures("singlePlayerButton.png", "singlePlayerButtonPressed.png");
    
    multiplayerButton->loadTextures("multiplayerButton.png", "multiplayerButtonPressed.png");
    

    singlePlayerButton->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.4f));
    multiplayerButton->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.25f));
    
    singlePlayerButton->addTouchEventListener(CC_CALLBACK_2(Lobby::singlePlayerPressed, this));
    
    multiplayerButton->addTouchEventListener(CC_CALLBACK_2(Lobby::multiplayerPressed, this));
    
    this->addChild(logo);
    this->addChild(singlePlayerButton);
    this->addChild(multiplayerButton);
}

void Lobby::singlePlayerPressed(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        SceneManager::getInstance()->enterGameScene(false);
    }
}

void Lobby::multiplayerPressed(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        SceneManager::getInstance()->showPeerList();
    }
}










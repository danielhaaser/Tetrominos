//
//  SceneManager.cpp
//  Tetrominos
//
//  Created by Daniel Haaser on 7/1/15.
//
//

#include "SceneManager.h"
#include "GameScene.h"

using namespace cocos2d;

#pragma mark -
#pragma mark Lifecycle

static SceneManager* sharedInstance = nullptr;

SceneManager* SceneManager::getInstance()
{
    if (!sharedInstance)
    {
        sharedInstance = new (std::nothrow)SceneManager();
    }
    
    return sharedInstance;
}

SceneManager::SceneManager()
{
    this->gameScene = nullptr;
    this->networkingWrapper = std::unique_ptr<NetworkingWrapper>(new NetworkingWrapper());
    this->networkingWrapper->setDelegate(this);
}

SceneManager::~SceneManager()
{
    
}

#pragma mark -
#pragma mark Public Methods

void SceneManager::enterGameScene(bool networked)
{
    Scene* scene = Scene::create();
    this->gameScene = GameScene::create();
    this->gameScene->setNetworkedSession(networked);
    
    scene->addChild(this->gameScene);
    
    Director::getInstance()->pushScene(scene);
}

void SceneManager::returnToLobby()
{
    if (gameScene)
    {
        Director::getInstance()->popScene();
        gameScene = nullptr;
        networkingWrapper->disconnect();
    }
}

void SceneManager::showPeerList()
{
    networkingWrapper->showPeerList();
}

void SceneManager::receiveMultiplayerInvitations()
{
    networkingWrapper->startAdvertisingAvailability();
}

void SceneManager::sendData(const void *data, unsigned long length)
{
    networkingWrapper->sendData(data, length);
}

#pragma mark -
#pragma mark NetworkingWrapper Delegate Methods

void SceneManager::receivedData(const void *data, unsigned long length)
{
    if (gameScene)
    {
        gameScene->receivedData(data, length);
    }
}

void SceneManager::stateChanged(ConnectionState state)
{
    switch (state)
    {
        case ConnectionState::CONNECTING:
            CCLOG("Connecting...");
            break;
            
        case ConnectionState::NOT_CONNECTED:
            CCLOG("Not Connected");
            break;
            
        case ConnectionState::CONNECTED:
            CCLOG("Connected");
            if (!gameScene)
            {
                this->networkingWrapper->stopAdvertisingAvailability();
                this->enterGameScene(true);
            }
            break;
    }
}


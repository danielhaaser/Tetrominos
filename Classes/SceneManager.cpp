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
    
}

SceneManager::~SceneManager()
{
    
}

#pragma mark -
#pragma mark Public Methods

void SceneManager::enterGameScene(bool networked)
{
    Scene* scene = Scene::create();
    GameScene* gameScene = GameScene::create();
    
    scene->addChild(gameScene);
    
    Director::getInstance()->pushScene(scene);
}


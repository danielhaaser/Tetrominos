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
#include "Tetromino.h"
#include "Coordinate.h"
#include <time.h>

using namespace cocos2d;

#pragma mark -
#pragma mark Lifecycle

bool GameScene::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    LayerColor* background = LayerColor::create(Color4B(255, 255, 255, 255));
    this->addChild(background);
    this->tetrominoBag = std::unique_ptr<TetrominoBag>(new TetrominoBag());
    this->active = false;
    
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
    
    this->setupTouchHandling();
    
    this->setGameActive(true);
}

void GameScene::setupTouchHandling()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    
    static Vec2 firstTouchPos;
    static Vec2 lastTouchPos;
    static bool allowRotate = true;
    static std::clock_t touchStartedTime;
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        allowRotate = true;
        firstTouchPos = this->convertTouchToNodeSpace(touch);
        lastTouchPos = firstTouchPos;
        touchStartedTime = clock();
        return true;
    };
    
    touchListener->onTouchMoved = [&](Touch* touch, Event* event)
    {
        Vec2 touchPos = this->convertTouchToNodeSpace(touch);
        Vec2 difference = touchPos - lastTouchPos;

        Tetromino* activeTetromino = grid->getActiveTetromino();
        
        if (activeTetromino)
        {
            Coordinate differenceCoordinate = this->convertPositionToCoordinate(difference);
            Coordinate activeTetrominoCoordinate = grid->getActiveTetrominoCoordinate();
            
            if (differenceCoordinate.y <= -1)
            {
                Coordinate newTetrominoCoordinate = Coordinate(activeTetrominoCoordinate.x, activeTetrominoCoordinate.y - 1);
                
                grid->setActiveTetrominoCoordinate(newTetrominoCoordinate);
                
                lastTouchPos = touchPos;
            }
            else if (abs(differenceCoordinate.x) >= 1)
            {
                bool movingRight = (differenceCoordinate.x > 0);
                
                Coordinate newTetrominoCoordinate = Coordinate(activeTetrominoCoordinate.x + (movingRight ? 1 : -1), activeTetrominoCoordinate.y);
                
                grid->setActiveTetrominoCoordinate(newTetrominoCoordinate);
                allowRotate = false;
                lastTouchPos = touchPos;
            }
        }
    };
    
    touchListener->onTouchEnded = [&](Touch* touch, Event* event)
    {
        if (this->grid->getActiveTetromino())
        {
            Vec2 touchEndPos = this->convertTouchToNodeSpace(touch);
            float distance = touchEndPos.distance(firstTouchPos);
            Size blockSize = this->grid->getBlockSize();
            
            if (distance < blockSize.width && allowRotate)
            {
                grid->rotateActiveTetromino();
            }
            else
            {
                Vec2 difference = touchEndPos - firstTouchPos; // maybe use firstTouchPos?
                std::clock_t clockDifference = clock() - touchStartedTime;
                
                if (clockDifference <= 0)
                {
                    return;
                }
                
                float touchDuration = (float) (clockDifference) / CLOCKS_PER_SEC;
                float velocity = fabsf(difference.y / touchDuration);
                
                if (velocity > DROP_VELOCITY)
                {
                    CCLOG("DROP! Velocity was %f", velocity);
                    this->grid->dropActiveTetromino();
                    
                }
            }
        }
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

#pragma mark -
#pragma mark Public Methods

#pragma mark -
#pragma mark Protected Methods

Tetromino* GameScene::createRandomTetromino()
{
    TetrominoType tetrominoType = tetrominoBag->getTetromino();
    
    Tetromino* newTetromino = Tetromino::createWithType(tetrominoType);
    
    return newTetromino;
}

void GameScene::setGameActive(bool active)
{
    this->active = active;
    
    if (active)
    {
        this->schedule(CC_SCHEDULE_SELECTOR(GameScene::step), INITIAL_STEP_INTERVAL);
    }
    else
    {
        this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::step));
    }
}

void GameScene::step(float dt)
{
    Tetromino* activeTetromino = grid->getActiveTetromino();
    
    if (!activeTetromino)
    {
        Tetromino* newTetromino = this->createRandomTetromino();
        this->grid->spawnTetromino(newTetromino);
    }
    else
    {
        this->grid->step();
    }
}

#pragma mark -
#pragma mark UI Methods

void GameScene::backButtonPressed(cocos2d::Ref *pSender, cocos2d::ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        SceneManager::getInstance()->returnToLobby();
    }
}

#pragma mark -
#pragma mark Utility Methods

Coordinate GameScene::convertPositionToCoordinate(Vec2 position)
{
    Size blockSize = this->grid->getBlockSize();
    
    return Coordinate(position.x / blockSize.width, position.y / blockSize.height);
}
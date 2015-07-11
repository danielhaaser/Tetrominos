//
//  Tetromino.cpp
//  Tetrominos
//
//  Created by Daniel Haaser on 7/1/15.
//
//

#include "Tetromino.h"
#include "JSONPacker.h"

#define GRID_SIZE 4

using namespace cocos2d;

#pragma mark -
#pragma mark Lifecycle

Tetromino* Tetromino::createWithType(TetrominoType type)
{
    Tetromino* tetromino = new (std::nothrow) Tetromino();
    
    if (tetromino && tetromino->initWithType(type))
    {
        tetromino->autorelease();
        return tetromino;
    }
        
    CC_SAFE_DELETE(tetromino);
    return nullptr;
}

bool Tetromino::initWithType(TetrominoType type)
{
    if (! Node::init())
    {
        return false;
    }
    
    this->type = type;
    rotations = std::vector<std::vector<Coordinate>>();
    
    std::string jsonString = FileUtils::getInstance()->getStringFromFile("tetrominos.json");
    
    JSONPacker::TetrominoState tetrominoState = JSONPacker::unpackTetrominoJSON(jsonString, type);
    
    this->color = tetrominoState.color;
    this->rotations = tetrominoState.rotations;
    
    this->blocks = std::vector<Sprite*>();
    this->blocks.reserve(BLOCKS_PER_TETROMINO);
    
    this->rotationIndex = 0;
    
    Sprite* dummyBlock = Sprite::create("block.png");
    Size dummySize = dummyBlock->getContentSize();
    
    float gridSizeF = float(GRID_SIZE);
    this->setContentSize(Size(dummySize.width * gridSizeF, dummySize.height * gridSizeF));
    
    auto coordinates = rotations[this->rotationIndex];
    
    for (Coordinate coordinate : coordinates)
    {
        Sprite* block = Sprite::create("block.png");
        block->setColor(this->color);
        
        block->setAnchorPoint(Vec2(0.0f, 0.0f));
        block->setPosition(Vec2(coordinate.x * dummySize.width, coordinate.y * dummySize.height));
        
        this->addChild(block);
        blocks.push_back(block);
    }
    
    return true;
}

#pragma mark -
#pragma mark Public Methods

void Tetromino::rotate(bool right)
{
    if (right)
    {
        rotationIndex++;
    }
    else
    {
        rotationIndex--;
    }
    
    if (rotationIndex >= (int) rotations.size()) 
    {
        rotationIndex = 0;
    }
    else if (rotationIndex < 0)
    {
        rotationIndex = (int) rotations.size() - 1;
    }
    
    auto coordinates = rotations[this->rotationIndex];
    
    for (int index = 0; index < GRID_SIZE; ++index)
    {
        Sprite* block = blocks[index];
        Coordinate coordinate = coordinates[index];
        
        Size blockSize = block->getContentSize();
        block->setPosition(Vec2(coordinate.x * blockSize.width, coordinate.y * blockSize.height));
    }
}

int Tetromino::getHighestYCoordinate()
{
    auto coordinates = this->getCurrentRotation();
    
    int highest = 0;
    
    for (Coordinate coordinate : coordinates)
    {
        if (coordinate.y > highest)
        {
            highest = coordinate.y;
        }
    }
    
    return highest;
}

int Tetromino::getWidthInBlocks()
{
    auto coordinates = this->getCurrentRotation();
    
    int rightMost = 0;
    int leftMost = GRID_SIZE;
    
    for (Coordinate coordinate : coordinates)
    {
        if (coordinate.x < leftMost)  // NO SEMICOLON!!!!!
        {
            leftMost = coordinate.x;
        }
        
        if (coordinate.x > rightMost)
        {
            rightMost = coordinate.x;
        }
    }
    
    return rightMost - leftMost + 1;
}

int Tetromino::getMinimumXCoordinate()
{
    auto coordinates = this->getCurrentRotation();
    
    int leftMost = GRID_SIZE;
    
    for (Coordinate coordinate : coordinates)
    {
        if (coordinate.x < leftMost)
        {
            leftMost = coordinate.x;
        }
    }
    
    return leftMost;
}

std::vector<int> Tetromino::getSkirt()
{
    int width = this->getWidthInBlocks();
    int skirtStart = this->getMinimumXCoordinate();
    
    std::vector<int> skirt = std::vector<int>(width, GRID_SIZE - 1);
    
    auto coordinates = this->getCurrentRotation();
    
    for (Coordinate coordinate : coordinates)
    {
        int x = coordinate.x - skirtStart;
        int skirtY = skirt[x];
        
        if (coordinate.y < skirtY)
        {
            skirt[x] = coordinate.y;
        }
    }
    
    return skirt;
}

TetrominoType Tetromino::getTetrominoType()
{
    return this->type;
}

std::vector<Sprite*> Tetromino::getBlocks()
{
    return blocks;
}

std::vector<Coordinate> Tetromino::getCurrentRotation()
{
    return rotations[rotationIndex];
}

Color3B Tetromino::getTetrominoColor()
{
    return this->color;
}

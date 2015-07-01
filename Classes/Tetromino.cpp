//
//  Tetromino.cpp
//  Tetrominos
//
//  Created by Daniel Haaser on 7/1/15.
//
//

#include "Tetromino.h"

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
    
    
    
    return true;
}
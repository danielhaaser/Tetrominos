//
//  Grid.cpp
//  Tetrominos
//
//  Created by Daniel Haaser on 7/1/15.
//
//

#include "Grid.h"
#include "Tetromino.h"

#pragma mark -
#pragma mark Lifecycle

bool Grid::init()
{
    if (! Sprite::initWithFile("grid.png"))
    {
        return false;
    }
    
    this->activeTetromino = nullptr;
    
    return true;
}

void Grid::onEnter()
{
    Sprite::onEnter();
}

#pragma mark -
#pragma mark Public Methods

void Grid::rotateActiveTetromino()
{
    if (this->activeTetromino)
    {
        this->activeTetromino->rotate(true);
    }
    
    //TODO: Check if collision, undo rotation
}

void Grid::spawnTetromino(Tetromino *tetromino)
{
    this->activeTetromino = tetromino;
    
    this->addChild(this->activeTetromino);
    
    // TODO: Place tetromino in correct position in grid
}















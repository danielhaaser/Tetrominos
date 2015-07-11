//
//  Grid.h
//  Tetrominos
//
//  Created by Daniel Haaser on 7/1/15.
//
//

#ifndef __Tetrominos__Grid__
#define __Tetrominos__Grid__

#include "cocos2d.h"
#include "Coordinate.h"

class Tetromino;

class Grid : public cocos2d::Sprite
{
public:
    CREATE_FUNC(Grid);
    
    void rotateActiveTetromino();
    void spawnTetromino(Tetromino* tetromino);
    void step();
    
    void setActiveTetrominoCoordinate(Coordinate coordinate);
    Coordinate getActiveTetrominoCoordinate();
    cocos2d::Size getBlockSize();
    Tetromino* getActiveTetromino();
    int getTotalLinesCleared();
    int getScore();
    void dropActiveTetromino();
    bool checkIfTopReached();
    std::vector<std::vector<cocos2d::Sprite*>> getBlocksLanded();
    
private:
    Tetromino* activeTetromino;
    Tetromino* ghostTetromino;
    Coordinate activeTetrominoCoordinate;
    int score;
    int totalLinesCleared;
    std::vector<std::vector<cocos2d::Sprite*>> blocksLanded;
    
    bool init() override;
    void onEnter() override;
    cocos2d::Vec2 convertCoordinateToPosition(Coordinate coordinate);
    bool checkIfTetrominoCollides(Tetromino* tetromino, Coordinate tetrominoCoordinate);
    void deactivateTetromino(Tetromino* tetromino, Coordinate tetrominoCoordinate);
    void placeTetrominoOnBoard(Tetromino* tetromino, Coordinate tetrominoCoordinate);
    Coordinate getTetrominoLandingCoordinate();
    void clearLines();
    void updateGhostTetrominoPosition();
    void updateScore(int linesCleared);
};

#endif /* defined(__Tetrominos__Grid__) */










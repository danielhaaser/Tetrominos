//
//  TetrominoBag.h
//  Tetrominos
//
//  Created by Daniel Haaser on 7/2/15.
//
//

#ifndef __Tetrominos__TetrominoBag__
#define __Tetrominos__TetrominoBag__

#include "Constants.h"

class TetrominoBag
{
public:
    TetrominoBag();
    
    TetrominoType getTetromino();
    
private:
    std::vector<TetrominoType> bag;
    std::default_random_engine randomGenerator;
};

#endif /* defined(__Tetrominos__TetrominoBag__) */

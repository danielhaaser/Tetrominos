//
//  JSONPacker.h
//  Tetrominos
//
//  Created by Daniel Haaser on 7/1/15.
//
//

#ifndef __Tetrominos__JSONPacker__
#define __Tetrominos__JSONPacker__

#include "cocos2d.h"
#include "Coordinate.h"
#include "Constants.h"

namespace JSONPacker
{
    struct TetrominoState
    {
        cocos2d::Color3B color;
        std::vector<std::vector<Coordinate>> rotations;
    };
    
    TetrominoState unpackTetrominoJSON(std::string json, TetrominoType type);
}

#endif /* defined(__Tetrominos__JSONPacker__) */

//
//  Lobby.h
//  Tetrominos
//
//  Created by Daniel Haaser on 7/1/15.
//
//

#ifndef __Tetrominos__Lobby__
#define __Tetrominos__Lobby__

#include "cocos2d.h"

class Lobby : public cocos2d::Node
{
public:
    CREATE_FUNC(Lobby);
    
private:
    bool init() override;
};

#endif /* defined(__Tetrominos__Lobby__) */

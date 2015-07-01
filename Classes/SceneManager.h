//
//  SceneManager.h
//  Tetrominos
//
//  Created by Daniel Haaser on 7/1/15.
//
//

#ifndef __Tetrominos__SceneManager__
#define __Tetrominos__SceneManager__

class SceneManager
{
public:
    static SceneManager* getInstance();
    
    void enterGameScene(bool networked);
    
private:
    SceneManager();
    ~SceneManager();
};

#endif /* defined(__Tetrominos__SceneManager__) */

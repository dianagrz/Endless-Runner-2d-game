#ifndef __PLAYGAME_SCENE_H__
#define __PLAYGAME_SCENE_H__

#include "cocos2d.h"
//#include "Obstacles.h"

class PlayGame : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);

    void GenerateObstacles();

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    //void spawnObstacle(float dt);
    //Obstacles obstacles;

    //cocos2d::Sprite* spriteCharacter;

    CREATE_FUNC(PlayGame);
};

#endif // __PLAYGAME_SCENE_H__

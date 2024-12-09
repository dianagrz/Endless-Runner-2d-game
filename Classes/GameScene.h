#ifndef __PLAYGAME_SCENE_H__
#define __PLAYGAME_SCENE_H__

#include "cocos2d.h"
//#include "Obstacles.h"

class PlayGame : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int highestScore);

    virtual bool init();

    void update(float dt);

    void menuCloseCallback(cocos2d::Ref* pSender);

    void GenerateObstacles();
    void createFish(cocos2d::Point position, cocos2d::MoveBy* movement, cocos2d::Size visibleSize);
    void createCoin(cocos2d::Point position, cocos2d::MoveBy* movement, cocos2d::Size visibleSize);
    void createShell(cocos2d::Point position, cocos2d::MoveBy* movement, cocos2d::Size visibleSize);
    void createUrchin(cocos2d::Point position, cocos2d::MoveBy* movement, cocos2d::Size visibleSize);

    void pickCollectible(cocos2d::PhysicsBody* body);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void loseGame();

    bool onContactBegin(cocos2d::PhysicsContact& contact);

    #define COLLECTIBLE_CATEGORY_BITMASK 0x01

    #define CHARACTER_COLLISION_BITMASK 0x01
    #define OBSTACLE_COLLISION_BITMASK 0x02
    #define COIN_COLLISION_BITMASK 0x03
    #define SHELL_COLLISION_BITMASK 0x04
    #define URCHIN_COLLISION_BITMASK 0x05
    #define EDGE_COLLISION_BITMASK 0x06

    CREATE_FUNC(PlayGame);
};

#endif // __PLAYGAME_SCENE_H__

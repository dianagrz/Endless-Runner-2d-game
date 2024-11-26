#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameOver : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int currScore, int highScore);

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);

    void playGame(cocos2d::Ref* pSender);

    cocos2d::Sprite mySprite;
    
    CREATE_FUNC(GameOver);
};

#endif // __GAMEOVER_SCENE_H__

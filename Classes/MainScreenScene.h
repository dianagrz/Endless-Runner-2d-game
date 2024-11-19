#ifndef __MAINSCREEN_SCENE_H__
#define __MAINSCREEN_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MainScreen : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    void menuCloseCallback(cocos2d::Ref* pSender);

    void playGame(cocos2d::Ref* pSender);

    cocos2d::Sprite mySprite;
    
    CREATE_FUNC(MainScreen);
};

#endif // __MAINSCREEN_SCENE_H__

#include "GameOverScene.h"
#include "ui/CocosGUI.h":

#include "MainScreenScene.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    return GameOver::create();
}

bool GameOver::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("background.jpg");
    background->setScale(visibleSize.width/background->getContentSize().width, visibleSize.height/ background->getContentSize().height);
    background->setAnchorPoint(Vec2(0, 0));
    background->setPosition(Point(0, 0));
    this->addChild(background);

    auto labelTitle = Label::createWithTTF("GAME OVER", "fonts/CherryBombOne-Regular.ttf", 80);
    labelTitle->setPosition(Point(visibleSize.width / 2, 2*visibleSize.height / 3));
    labelTitle->setColor(Color3B(255, 163, 181));
    this->addChild(labelTitle);

    auto playButton = MenuItemFont::create("PLAY", CC_CALLBACK_1(GameOver::playGame, this));
    playButton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    playButton->setFontName("fonts/CherryBombOne-Regular.ttf");

    auto menu = Menu::create(playButton, NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);
    

    return true;
}


void GameOver::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void GameOver::playGame(Ref* pSender)
{
    auto scene = MainScreen::createScene();
    Director::getInstance()->replaceScene(scene);
}
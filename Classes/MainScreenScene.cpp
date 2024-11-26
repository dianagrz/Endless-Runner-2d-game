#include "MainScreenScene.h"
#include "ui/CocosGUI.h":

#include "GameScene.h"

USING_NS_CC;

Scene* MainScreen::createScene()
{
    return MainScreen::create();
}

bool MainScreen::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("background.jpg");
    background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
    background->setAnchorPoint(Vec2(0, 0));
    background->setPosition(Point(0, 0));
    this->addChild(background);

    auto labelTitle = Label::createWithTTF("Go With The Flow", "fonts/CherryBombOne-Regular.ttf", 80);
    labelTitle->setPosition(Point(visibleSize.width / 2, 2 * visibleSize.height / 3));
    labelTitle->setColor(Color3B(255, 163, 181));
    this->addChild(labelTitle);

    auto playButton = MenuItemFont::create("PLAY", CC_CALLBACK_1(MainScreen::playGame, this));
    playButton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    playButton->setFontName("fonts/CherryBombOne-Regular.ttf");

    auto menu = Menu::create(playButton, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);


    return true;
}


void MainScreen::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void MainScreen::playGame(Ref* pSender)
{
    auto scene = PlayGame::createScene(0);
    Director::getInstance()->replaceScene(scene);
}
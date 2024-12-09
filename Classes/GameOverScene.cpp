#include "GameOverScene.h"
#include "ui/CocosGUI.h":
#include "audio/include/AudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

static int SCORE = 0;
static int  HIGHEST_SCORE;
static int backgroundMusic;

Scene* GameOver::createScene(int currScore, int highScore)
{
    SCORE = currScore;
    HIGHEST_SCORE = highScore;
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
    labelTitle->setPosition(Point(visibleSize.width / 2, 3*visibleSize.height / 4));
    labelTitle->setColor(Color3B(255, 163, 181));
    this->addChild(labelTitle);

    auto playButton = MenuItemImage::create("playAgain.png","playAgain.png", CC_CALLBACK_1(GameOver::playGame, this));
    playButton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    playButton->setScale(0.25 * visibleSize.height / playButton->getContentSize().height, 0.1 * visibleSize.width / playButton->getContentSize().width);

    auto scoreLabel = Label::createWithTTF("Score: " + std::to_string(SCORE), "fonts/CherryBombOne-Regular.ttf", 30);
    scoreLabel->setPosition(Point(visibleSize.width / 2, visibleSize.height / 3));
    scoreLabel->setColor(Color3B(255, 163, 181));
    this->addChild(scoreLabel);

    auto highScoreLabel = Label::createWithTTF("Highest Score: " + std::to_string(HIGHEST_SCORE), "fonts/CherryBombOne-Regular.ttf", 30);
    highScoreLabel->setPosition(Point(visibleSize.width / 2, visibleSize.height / 4));
    highScoreLabel->setColor(Color3B(255, 163, 181));
    this->addChild(highScoreLabel);

    auto menu = Menu::create(playButton, NULL);
    menu->setPosition(Point(0,0));
    this->addChild(menu);
    
    backgroundMusic = cocos2d::AudioEngine::play2d("audio/MenuSong.mp3", true, 1.0F);
    
    return true;
}


void GameOver::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void GameOver::playGame(Ref* pSender)
{
    auto scene = PlayGame::createScene(HIGHEST_SCORE);
    cocos2d::AudioEngine::stop(backgroundMusic);
    Director::getInstance()->replaceScene(scene);
}
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
    labelTitle->setPosition(Point(visibleSize.width / 2, 2*visibleSize.height / 3));
    labelTitle->setColor(Color3B(255, 163, 181));
    this->addChild(labelTitle);

    auto playButton = MenuItemFont::create("PLAY AGAIN", CC_CALLBACK_1(GameOver::playGame, this));
    playButton->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    playButton->setFontName("fonts/CherryBombOne-Regular.ttf");

    auto scoreLabel = MenuItemFont::create("Score: " + std::to_string(SCORE));
    scoreLabel->setFontName("fonts/CherryBombOne-Regular.ttf");
    scoreLabel->setPosition(Point(visibleSize.width / 2, visibleSize.height / 3));
    auto highScoreLabel = MenuItemFont::create("Highest Score: " + std::to_string(HIGHEST_SCORE));
    highScoreLabel->setFontName("fonts/CherryBombOne-Regular.ttf");
    highScoreLabel->setPosition(Point(visibleSize.width / 2, visibleSize.height / 4));


    auto menu = Menu::create(playButton, scoreLabel, highScoreLabel, NULL);
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
#include "GameScene.h"
#include "MainScreenScene.h"
#include "GameOverScene.h"
#include "audio/include/AudioEngine.h"
USING_NS_CC;

static int SCORE;
static int HIGHEST_SCORE;
static Label* scoreLabel;
static int backgroundMusic;
static bool doublePoints;
static float powerUpTime;
static Sprite* spriteCharacter;
static Size visibleSize;

Scene* PlayGame::createScene(int highestScore)
{
    SCORE = 0;
    HIGHEST_SCORE = highestScore;
    doublePoints = false;
    powerUpTime = 0.0f;
    auto scene = Scene::createWithPhysics();

    auto layer = PlayGame::create();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    scene->addChild(layer);

    backgroundMusic = cocos2d::AudioEngine::play2d("audio/GameSong.mp3", true, 1.0F);

    return scene;
}

bool PlayGame::init()
{
    if (!Scene::init())
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto background = Sprite::create("background.jpg");
    background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);
    background->setAnchorPoint(Vec2(0, 0));
    background->setPosition(Point(0, 0));
    this->addChild(background);

    //create an edge body to detect when the obstacles objects have left the screen
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize * 1.5, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCollisionBitmask(EDGE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    spriteCharacter = Sprite::create("stingray.png");
    spriteCharacter->setScale(0.125 * visibleSize.height / spriteCharacter->getContentSize().height, 0.125 * visibleSize.height / spriteCharacter->getContentSize().height);
    spriteCharacter->setAnchorPoint(Vec2(0.5, 0.5));
    spriteCharacter->setPosition(Point((visibleSize.width / 5), (4 * visibleSize.height / 8)));
    auto characterBody = PhysicsBody::createBox(spriteCharacter->getContentSize());
    characterBody->setDynamic(false);
    characterBody->setCollisionBitmask(CHARACTER_COLLISION_BITMASK);
    characterBody->setCategoryBitmask(COLLECTIBLE_CATEGORY_BITMASK);
    characterBody->setContactTestBitmask(true);
    spriteCharacter->setPhysicsBody(characterBody);
    this->addChild(spriteCharacter);

    scoreLabel = Label::createWithTTF(std::to_string(SCORE), "fonts/CherryBombOne-Regular.ttf", 50);
    scoreLabel->setColor(Color3B(255, 163, 181));
    scoreLabel->setPosition(Point(visibleSize.width * 0.1 + origin.x, visibleSize.height * 0.9 + origin.y));
    this->addChild(scoreLabel, 10);

    //create listener to move the character when the up and down key arrows are pressed
    auto moveListener = EventListenerKeyboard::create();

    moveListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
        auto pos = spriteCharacter->getPosition();
        if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
            auto moveDown = MoveBy::create(0.5, Point(0, -visibleSize.height / 4));
            spriteCharacter->runAction(moveDown);
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
            auto moveUp = MoveBy::create(0.5, Point(0, visibleSize.height / 4));
            spriteCharacter->runAction(moveUp);
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(moveListener, this);

    //create listener to detect collisions between the different objects on screen
    auto collisionListener = EventListenerPhysicsContact::create();
    collisionListener->onContactBegin = CC_CALLBACK_1(PlayGame::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(collisionListener, this);

    schedule([&](float delta) { GenerateObstacles(); }, 1.8f, "GenerateObstacles");
    this->scheduleUpdate();

    return true;
}

void PlayGame::update(float dt) {
    //to control the duration of powerups
    if (powerUpTime > 0.f) {
        powerUpTime -= dt;
        if (powerUpTime <= 0.f) {
            powerUpTime = 0;
            doublePoints = false;
        }
    }

    //to prevent the character from moving out of the designated lanes
    auto pos = spriteCharacter->getPosition();
    if (pos.y < visibleSize.height / 4) {
        spriteCharacter->setPosition(Point(pos.x, visibleSize.height / 4));
    }
    else if (pos.y > 3 * visibleSize.height / 4) {
        spriteCharacter->setPosition(Point(pos.x, 3 * visibleSize.height / 4));
    }

    //Losing alternative
    if (SCORE < 0) {
        loseGame();
    }
}

void PlayGame::GenerateObstacles() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int options[7][3] = { {0,0,0}, {1,0,0}, {0,1,0}, {0,0,1}, {0,1,1}, {1,0,1}, {1,1,0} };

    auto random = rand() % 7;

    Point topPosition = Point(visibleSize.width * 1.15, 6 * visibleSize.height / 8);
    Point middlePosition = Point(visibleSize.width * 1.15, 4 * visibleSize.height / 8);
    Point bottomPosition = Point(visibleSize.width * 1.15, 2 * visibleSize.height / 8);;

    double speed = 7 - 0.2 * SCORE;
    if (speed < 2) speed = 2;
    auto movement = MoveBy::create(speed, Point(-visibleSize.width * 1.5, 0));

    if (options[random][0] == 1) {
        createFish(topPosition, movement, visibleSize);
    }
    else {
        if (rand() % 15 == 13) {
            createShell(topPosition, movement, visibleSize);
        }
        else if (rand() % 2 == 1) {
            createCoin(topPosition, movement, visibleSize);
        }
    }

    if (options[random][1] == 1) {
        createFish(middlePosition, movement, visibleSize);
    }
    else {
        int randomCollectible = rand();
        if (randomCollectible % 15 == 13) {
            createShell(middlePosition, movement, visibleSize);
        }
        else if (randomCollectible % 15 == 12) {
            createUrchin(middlePosition, movement, visibleSize);
        }
        else if (randomCollectible % 2 == 1) {
            createCoin(middlePosition, movement, visibleSize);
        }
    }

    if (options[random][2] == 1) {
        createFish(bottomPosition, movement, visibleSize);
    }
    else {
        int randomCollectible = rand();
        if (rand() % 15 == 13) {
            createShell(bottomPosition, movement, visibleSize);
        }
        else if (rand() % 2 == 1) {
            createCoin(bottomPosition, movement, visibleSize);
        }
    }

}

void PlayGame::createFish(Point position, MoveBy* movement, Size visibleSize) {
    auto fishSprite = Sprite::create("fish.png");
    fishSprite->setScale(0.125 * visibleSize.height / fishSprite->getContentSize().height, 0.125 * visibleSize.height / fishSprite->getContentSize().height);
    fishSprite->setPosition(position);

    auto fishBody = PhysicsBody::createBox(fishSprite->getContentSize());
    fishBody->setDynamic(false);
    fishSprite->setPhysicsBody(fishBody);
    fishBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    fishBody->setContactTestBitmask(true);

    this->addChild(fishSprite);
    fishSprite->runAction(movement->clone());
}

void PlayGame::createCoin(Point position, MoveBy* movement, Size visibleSize) {
    auto coinSprite = Sprite::create("coin.png");
    coinSprite->setScale(0.1 * visibleSize.height / coinSprite->getContentSize().height, 0.1 * visibleSize.height / coinSprite->getContentSize().height);
    coinSprite->setPosition(position);

    auto coinBody = PhysicsBody::createBox(coinSprite->getContentSize());
    coinBody->setDynamic(false);
    coinSprite->setPhysicsBody(coinBody);
    coinBody->setCollisionBitmask(COIN_COLLISION_BITMASK);
    coinBody->setCategoryBitmask(COLLECTIBLE_CATEGORY_BITMASK);
    coinBody->setContactTestBitmask(true);

    this->addChild(coinSprite);
    coinSprite->runAction(movement->clone());
}

void PlayGame::createShell(Point position, MoveBy* movement, Size visibleSize) {
    auto shellSprite = Sprite::create("shell.png");
    shellSprite->setScale(0.1 * visibleSize.height / shellSprite->getContentSize().height, 0.1 * visibleSize.height / shellSprite->getContentSize().height);
    shellSprite->setPosition(position);

    auto shellBody = PhysicsBody::createBox(shellSprite->getContentSize());
    shellBody->setDynamic(false);
    shellSprite->setPhysicsBody(shellBody);
    shellBody->setCollisionBitmask(SHELL_COLLISION_BITMASK);
    shellBody->setCategoryBitmask(COLLECTIBLE_CATEGORY_BITMASK);
    shellBody->setContactTestBitmask(true);

    this->addChild(shellSprite);
    shellSprite->runAction(movement->clone());
}

void PlayGame::createUrchin(Point position, MoveBy* movement, Size visibleSize) {
    auto urchinSprite = Sprite::create("urchin.png");
    urchinSprite->setScale(0.1 * visibleSize.height / urchinSprite->getContentSize().height, 0.1 * visibleSize.height / urchinSprite->getContentSize().height);
    urchinSprite->setPosition(position);

    auto urchinBody = PhysicsBody::createBox(urchinSprite->getContentSize());
    urchinBody->setDynamic(false);
    urchinSprite->setPhysicsBody(urchinBody);
    urchinBody->setCollisionBitmask(URCHIN_COLLISION_BITMASK);
    urchinBody->setCategoryBitmask(COLLECTIBLE_CATEGORY_BITMASK);
    urchinBody->setContactTestBitmask(true);

    this->addChild(urchinSprite);
    urchinSprite->runAction(movement->clone());
}

void PlayGame::loseGame() {
    HIGHEST_SCORE = std::max(SCORE, HIGHEST_SCORE);
    auto scene = GameOver::createScene(SCORE, HIGHEST_SCORE);
    auto lost = cocos2d::AudioEngine::play2d("resources/audio/lost.mp3", false);
    cocos2d::AudioEngine::stop(backgroundMusic);
    Director::getInstance()->replaceScene(scene);
}

void PlayGame::pickCollectible(PhysicsBody* body) {
    if (body->getCollisionBitmask() == COIN_COLLISION_BITMASK) {
        SCORE += ((int)doublePoints + 1);
        scoreLabel->setString(std::to_string(SCORE));

        auto coin = cocos2d::AudioEngine::INVALID_AUDIO_ID;
        if (coin == cocos2d::AudioEngine::INVALID_AUDIO_ID) {
            coin = cocos2d::AudioEngine::play2d("audio/coin.mp3", true, 2.0F);
        }
    }
    else if (body->getCollisionBitmask() == SHELL_COLLISION_BITMASK) {
        doublePoints = true;
        powerUpTime = 20.0f;
    }
    else if (body->getCollisionBitmask() == URCHIN_COLLISION_BITMASK) {
        SCORE -= 3;
        scoreLabel->setString(std::to_string(SCORE));
        if (doublePoints) {
            doublePoints = false;
            powerUpTime = 0.0f;
        }
    }
    body->getNode()->removeFromParentAndCleanup(true);
}

bool PlayGame::onContactBegin(cocos2d::PhysicsContact& contact) {
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    //USE if character picked up a collectible
    if (a->getCategoryBitmask() == b->getCategoryBitmask()) {
        if (a->getCollisionBitmask() == CHARACTER_COLLISION_BITMASK) {
            pickCollectible(b);
        }
        if (b->getCollisionBitmask() == CHARACTER_COLLISION_BITMASK) {
            pickCollectible(a);
        }
    }

    //LOSE if character touches an obstacle
    else if (a->getCollisionBitmask() == CHARACTER_COLLISION_BITMASK || b->getCollisionBitmask() == CHARACTER_COLLISION_BITMASK) {
        loseGame();
    }

    //DESTROY if obstacle or collectible reaches the end
    else if (a->getCollisionBitmask() == EDGE_COLLISION_BITMASK) {
        b->getNode()->removeFromParentAndCleanup(true);
    }
    else if (b->getCollisionBitmask() == EDGE_COLLISION_BITMASK) {
        a->getNode()->removeFromParentAndCleanup(true);
    }

    return true;
}
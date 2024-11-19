#include "GameScene.h"

USING_NS_CC;

Scene* PlayGame::createScene()
{
    auto scene = Scene::createWithPhysics();

    auto layer = PlayGame::create();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    scene->addChild(layer);
    return scene;
}

bool PlayGame::init()
{
    if ( !Scene::init() )
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

    auto spriteCharacter = Sprite::create("stingray.png");
    spriteCharacter -> setScale(0.125*visibleSize.height/spriteCharacter->getContentSize().height, 0.125*visibleSize.height / spriteCharacter->getContentSize().height);
    spriteCharacter->setAnchorPoint(Vec2(0.5,0.5));
    spriteCharacter->setPosition(Point((visibleSize.width/5), (4*visibleSize.height/8)));
    auto characterBody = PhysicsBody::createBox(spriteCharacter->getContentSize());
    characterBody->setDynamic(false);
    spriteCharacter->setPhysicsBody(characterBody);
    this->addChild(spriteCharacter);

    auto moveListener = EventListenerKeyboard::create();
    

    moveListener->onKeyPressed = [spriteCharacter, this](EventKeyboard::KeyCode keyCode, Event* event) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
            CCLOG("down pressed");
            auto moveDown = MoveBy::create(0.5, Point(0, visibleSize / 4));
            spriteCharacter->runAction(moveDown);
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
            CCLOG("up pressed");
            auto moveUp = MoveBy::create(0.5, Point(0, visibleSize / 4));
            spriteCharacter->runAction(moveUp);
        }
    };

    //AQUI ME QUEDE HACER LOS CHOQUES
    //auto collisionListener = 

        //CC_CALLBACK_2(PlayGame::onKeyPressed, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    schedule([&](float delta) { GenerateObstacles(); }, 2.5f, "GenerateObstacles");//el trcer parametro se usa si quieres salir del schedule
    //this->schedule( SEL_SCHEDULE( PlayGame::spawnObstacle ), 0.005);

    //auto repeat = Repeat::create(&PlayGame::GenerateObstacles(), 5);

    return true;
}

/***
void PlayGame::spawnObstacle(float dt)
{
    obstacles.spawnObstacle(this);
}
***/

/***
void PlayGame::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, Event* event) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        auto moveDown = MoveBy::create(0.01, Vec2(0, -1 * visibleSize/4));
        spriteCharacter->runAction(moveDown);
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
        auto moveUp = MoveBy::create(0.01, Vec2(0, visibleSize / 4));
        spriteCharacter->runAction(moveUp);
        break;
    }
}
***/


void PlayGame::GenerateObstacles() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int options[7][3] = { {0,0,0}, {1,0,0}, {0,1,0}, {0,0,1}, {0,1,1}, {1,0,1}, {1,1,0} };

    auto random = rand() % 7;

    auto topSprite = Sprite::create("fish.png");
    topSprite->setScale(0.125 * visibleSize.height / topSprite->getContentSize().height, 0.125 * visibleSize.height / topSprite->getContentSize().height);
    topSprite->setPosition(Point(visibleSize.width*1.25, 6 * visibleSize.height / 8));

    auto topBody = PhysicsBody::createBox(topSprite->getContentSize());
    topBody->setDynamic(false);
    topSprite->setPhysicsBody(topBody);

    auto middleSprite = Sprite::create("fish.png");
    middleSprite->setScale(0.125 * visibleSize.height / middleSprite->getContentSize().height, 0.125 * visibleSize.height / middleSprite->getContentSize().height);
    middleSprite->setPosition(Point(visibleSize.width * 1.25, 4 * visibleSize.height / 8));

    auto middleBody = PhysicsBody::createBox(middleSprite->getContentSize());
    middleBody->setDynamic(false);
    middleSprite->setPhysicsBody(middleBody);

    auto bottomSprite = Sprite::create("fish.png");
    bottomSprite->setScale(0.125 * visibleSize.height / bottomSprite->getContentSize().height, 0.125 * visibleSize.height / bottomSprite->getContentSize().height);
    bottomSprite->setPosition(Point(visibleSize.width * 1.25, 2 * visibleSize.height / 8));

    auto bottomBody = PhysicsBody::createBox(bottomSprite->getContentSize());
    bottomBody->setDynamic(false);
    bottomSprite->setPhysicsBody(bottomBody);

    auto movement = MoveBy::create(10, Point(-visibleSize.width * 1.5, 0));


    if (options[random][0] == 1) {
        this->addChild(topSprite);
        topSprite->runAction(movement->clone());
    }

    if (options[random][1] == 1) {
        this->addChild(middleSprite);
        middleSprite->runAction(movement->clone());
    }

    if (options[random][2] == 1) {
        this->addChild(bottomSprite);
        bottomSprite->runAction(movement->clone());
    }

}

void PlayGame::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

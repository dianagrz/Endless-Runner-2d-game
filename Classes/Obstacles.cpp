#include "Obstacles.h"
#include<cstdlib>
#include<vector>
USING_NS_CC;

void spawnObstacle(cocos2d::Scene* scene) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    int options[7][3] = { {0,0,0}, {1,0,0}, {0,1,0}, {0,0,1}, {0,1,1}, {1,0,1}, {1,1,0} };
    
    auto random = rand() % 7;

    auto topSprite = Sprite::create("fish.png");
    topSprite->setScale(0.125 * visibleSize.height / topSprite->getContentSize().height, 0.125 * visibleSize.height / topSprite->getContentSize().height);
    topSprite->setPosition(Point(visibleSize.width + topSprite->getContentSize().width, 5 * visibleSize.height / 8));

    auto middleSprite = Sprite::create("fish.png");
    middleSprite->setScale(0.125 * visibleSize.height / middleSprite->getContentSize().height, 0.125 * visibleSize.height / middleSprite->getContentSize().height);
    middleSprite->setPosition(Point(visibleSize.width + middleSprite->getContentSize().width, 3 * visibleSize.height / 8));
    
    auto bottomSprite = Sprite::create("fish.png");
    bottomSprite->setScale(0.125 * visibleSize.height / bottomSprite->getContentSize().height, 0.125 * visibleSize.height / bottomSprite->getContentSize().height);
    bottomSprite->setPosition(Point(visibleSize.width + bottomSprite->getContentSize().width, 2 * visibleSize.height / 8));

    auto movement = MoveBy::create(10, Point(-visibleSize.width * 1.5, 0));


    if (options[random][0]) {
        scene->addChild(topSprite);
        topSprite->runAction(movement->clone());
    }

    if (options[random][0]) {
        scene->addChild(middleSprite);
        middleSprite->runAction(movement->clone());
    }

    if (options[random][0]) {
        scene->addChild(bottomSprite);
        bottomSprite->runAction(movement->clone());
    }
}
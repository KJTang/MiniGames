#include "StartScene.h"

#include "PKScene.h"
#include "FriendListScene.h"
#include "PlayerSprite.h"

StartScene::StartScene() {}

StartScene::~StartScene() {}

bool StartScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();

    backgroundLayer = LayerColor::create(Color4B::ORANGE);
    this->addChild(backgroundLayer);

    menuLayer = Layer::create();
    this->addChild(menuLayer);

    btnPK = ButtonSprite::create("PK-0.png", "PK-1.png");
    menuLayer->addChild(btnPK);
    btnPK->setPosition(visibleSize.width*0.55, visibleSize.height*0.65);
    btnPK->setCallbackFunc([&]() {
        log("start");
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, PKScene::create()));
    });

    btnFriend = ButtonSprite::create("Friend-0.png", "Friend-1.png");
    menuLayer->addChild(btnFriend);
    btnFriend->setPosition(visibleSize.width*0.5, visibleSize.height*0.25);
    btnFriend->setCallbackFunc([&]() {
        log("friend");
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, FriendListScene::create()));
    });
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("1.plist");

    //auto sprite = Sprite::createWithSpriteFrameName("body/1.png");
    //this->addChild(sprite);
    //sprite->setPosition(visibleSize / 2);

    return true;
}
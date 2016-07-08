#include "FriendListScene.h"
#include "StartScene.h"

FriendListScene::FriendListScene() {}

FriendListScene::~FriendListScene() {}

bool FriendListScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();

    backgroundLayer = Layer::create();
    this->addChild(backgroundLayer);
    auto list = Sprite::create("FriendList.png");
    backgroundLayer->addChild(list);
    list->setPosition(visibleSize.width*0.5, visibleSize.height*0.5);

    menuLayer = Layer::create();
    this->addChild(menuLayer);

    btnBack = ButtonSprite::create("FriendBack-0.png", "FriendBack-1.png");
    menuLayer->addChild(btnBack);
    btnBack->setPosition(visibleSize.width*0.5, visibleSize.height*0.85);
    btnBack->setCallbackFunc([&]() {
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, StartScene::create()));
    });

    return true;
}
#include "ButtonSprite.h"

ButtonSprite::ButtonSprite() {}

ButtonSprite::~ButtonSprite() {}

ButtonSprite* ButtonSprite::create(const std::string &released, const std::string &pressed)
{
    ButtonSprite *pRet = new(std::nothrow) ButtonSprite();
    if (pRet && pRet->init(released, pressed)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = 0;
        return 0;
    }
}

bool ButtonSprite::init(const std::string &released, const std::string &pressed)
{
    if (!Sprite::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    callbackFunc = nullptr;

    btnPressed = Sprite::create(pressed);
    this->addChild(btnPressed);
    btnPressed->setVisible(false);

    btnReleased = Sprite::create(released);
    this->addChild(btnReleased);
    btnReleased->setVisible(true);

    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    touchListener->onTouchBegan = [&](Touch* touch, Event* event) {
        startPoint = touch->getLocation();
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        // relative position
        cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = cocos2d::Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
        if (rect.containsPoint(locationInNode)) {
            btnPressed->setVisible(true);
            btnReleased->setVisible(false);
            return true;
        }
        return false;
    };

    touchListener->onTouchEnded = [&](Touch* touch, Event* event) {
        endPoint = touch->getLocation();
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        btnPressed->setVisible(false);
        btnReleased->setVisible(true);
        if (endPoint.x - startPoint.x > -10 && endPoint.x - startPoint.x < 10 &&
            endPoint.y - startPoint.y > -10 && endPoint.y - startPoint.y < 10) {
            static_cast<ButtonSprite*>(target->getParent())->onClicked();
        }
        return true;
    };

    /* when use popScene to go back to the scene which add ButtonSprite,
    * it'll call ButtonSprite::onEnter once more,
    * so we should add eventlistener in ButtonSprite::init()
    * to make sure eventlistener only is registered once
    */
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, btnReleased);

    return true;
}

void ButtonSprite::onEnter()
{
    Sprite::onEnter();
    // when enter ButtonSprite, enable the eventlistener
    touchListener->setEnabled(true);
}

void ButtonSprite::onClicked()
{
    if (callbackFunc) {
        callbackFunc();
        //        touchListener->setEnabled(false);
    }
}

void ButtonSprite::setCallbackFunc(const std::function<void()> &func)
{
    callbackFunc = func;
}
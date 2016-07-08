#include "PlayerSprite.h"
#include "AudioRecord.h"

PlayerHead* PlayerHead::create(const std::string &source)
{
    PlayerHead *pRet = new(std::nothrow) PlayerHead();
    if (pRet && pRet->init(source)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool PlayerHead::init(const std::string &source)
{
    if (!Sprite::init()) {
        return false;
    }
    pic = Sprite::createWithSpriteFrameName(source);
    this->addChild(pic);
    return true;
}

void PlayerHead::act()
{
    this->runAction(RepeatForever::create(Sequence::create(
        MoveBy::create(0.1, Vec2(0, 20)),
        MoveBy::create(0.1, Vec2(0, -20)),
        NULL)
        ));
}

PlayerBody* PlayerBody::create(const std::string &source)
{
    PlayerBody *pRet = new(std::nothrow) PlayerBody();
    if (pRet && pRet->init(source)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool PlayerBody::init(const std::string &source)
{
    if (!Sprite::init()) {
        return false;
    }
    pic = Sprite::createWithSpriteFrameName(source);
    this->addChild(pic);
    return true;
}

void PlayerBody::act()
{
    this->runAction(RepeatForever::create(Sequence::create(
        MoveBy::create(0.1, Vec2(20, 0)),
        MoveBy::create(0.1, Vec2(-20, 0)),
        NULL)
        ));
}

PlayerHand* PlayerHand::create(const std::string &source)
{
    PlayerHand *pRet = new(std::nothrow) PlayerHand();
    if (pRet && pRet->init(source)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool PlayerHand::init(const std::string &source)
{
    if (!Sprite::init()) {
        return false;
    }
    pic = Sprite::createWithSpriteFrameName(source);
    this->addChild(pic);
    return true;
}

void PlayerHand::act()
{
    this->runAction(RepeatForever::create(Sequence::create(
        RotateBy::create(0.1, 10),
        RotateBy::create(0.1, -10),
        NULL)
        ));
}

PlayerSprite* PlayerSprite::create(bool dirct)
{
    PlayerSprite *pRet = new(std::nothrow) PlayerSprite();
    if (pRet && pRet->init(dirct)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool PlayerSprite::changeShape()
{
    this->schedule(schedule_selector(PlayerSprite::change), 0.1);
    return true;
}

void PlayerSprite::change(float dt)
{
    if (playerHead) {
        playerHead->removeFromParentAndCleanup(true);
        playerHead = nullptr;
    }
    if (playerBody) {
        playerBody->removeFromParentAndCleanup(true);
        playerBody = nullptr;
    }
    if (playerHand) {
        playerHand->removeFromParentAndCleanup(true);
        playerHand = nullptr;
    }
    // TODO
    char headFile[30], bodyFile[30], handFile[30];
    headinfo = rand() % 10;
    bodyinfo = rand() % 10;
    handinfo = rand() % 10;
    sprintf(headFile, "head/%d.png", headinfo);
    sprintf(bodyFile, "body/%d.png", bodyinfo);
    sprintf(handFile, "weapon/%d.png", handinfo);

    playerHead = PlayerHead::create(headFile);
    this->addChild(playerHead);
    playerHead->setPosition(0, 30);

    playerBody = PlayerBody::create(bodyFile);
    this->addChild(playerBody);
    playerBody->setPosition(0, 0);

    playerHand = PlayerHand::create(handFile);
    this->addChild(playerHand);
    playerHand->setPosition(20, 0);

    if (!direction) {
        this->setRotation(180);
    }
}

bool PlayerSprite::init(bool dirct)
{
    if (!Sprite::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    direction = dirct;
    strength = 0;

    playerHead = nullptr, playerBody = nullptr, playerHand = nullptr;

    return true;
}

bool PlayerSprite::scaleWithVoice()
{
    this->schedule(schedule_selector(PlayerSprite::scale), 0.3);
    return true;
}

void PlayerSprite::scale(float dt)
{
    log("scale");
    this->runAction(Sequence::create(
        // TODO
        ScaleTo::create(0.1, AudioRecord::getInst()->vol / 30.0f * 0.5),
        DelayTime::create(0.05),
        ScaleTo::create(0.1, 0.5),
        NULL
        ));

}

void PlayerSprite::setInfo(int info)
{
    if (playerHead) {
        playerHead->removeFromParentAndCleanup(true);
        playerHead = nullptr;
    }
    if (playerBody) {
        playerBody->removeFromParentAndCleanup(true);
        playerBody = nullptr;
    }
    if (playerHand) {
        playerHand->removeFromParentAndCleanup(true);
        playerHand = nullptr;
    }
    char headFile[30], bodyFile[30], handFile[30];
    this->strength = info / 1000;
    info %= 1000;
    sprintf(headFile, "head/%d.png", info/100);
    info %= 100;
    sprintf(bodyFile, "body/%d.png", info/10);
    info %= 10;
    sprintf(handFile, "weapon/%d.png", info);

    playerHead = PlayerHead::create(headFile);
    this->addChild(playerHead);
    playerHead->setPosition(0, 30);

    playerBody = PlayerBody::create(bodyFile);
    this->addChild(playerBody);
    playerBody->setPosition(0, 0);

    playerHand = PlayerHand::create(handFile);
    this->addChild(playerHand);
    playerHand->setPosition(20, 0);

    if (!direction) {
        this->setRotation(180);
    }
}

bool PlayerSprite::act()
{
    this->setScale(AudioRecord::getInst()->ave_vol / 30.0f * 0.5);
    if (direction) {
        this->runAction(Sequence::create(
            EaseBounceIn::create(MoveTo::create(1, Vec2(visibleSize.width*0.5, visibleSize.height*0.55))),
            DelayTime::create(1),
            CallFunc::create([&]() {
            this->removeFromParentAndCleanup(true);
        }),
            NULL
            ));
    }
    else {
            this->runAction(Sequence::create(
                EaseBounceIn::create(MoveTo::create(1, Vec2(visibleSize.width*0.5, visibleSize.height*0.65))),
                DelayTime::create(1),
                CallFunc::create([&]() {
                this->removeFromParentAndCleanup(true);
            }),
                NULL
                ));
    }
    playerHead->act();
    playerBody->act();
    playerHand->act();
    return true;
}
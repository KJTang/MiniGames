#include "PKScene.h"
#include "StartScene.h"
#include "FriendListScene.h"

bool PKScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    isPrepared = false;

    socketLayer = SocketTest::create();
    this->addChild(socketLayer);

    this->addChild(AudioRecord::create());

    myPlayer = PlayerSprite::create(true);
    this->addChild(myPlayer);
    myPlayer->setScale(0.5);
    myPlayer->setPosition(visibleSize.width*0.5, visibleSize.height*0.1);

    otherPlayer = PlayerSprite::create(false);
    this->addChild(otherPlayer);
    otherPlayer->setScale(0.5);
    otherPlayer->setPosition(visibleSize.width*0.5, visibleSize.height*0.9);

    //this->OnVoice();
    this->OnPrepare();

    return true;
}

void PKScene::update(float dt)
{
    if (isPrepared) {
        this->unscheduleUpdate();
        this->OnVoice();
    }
}

void PKScene::OnPrepare()
{
    //this->scheduleUpdate();
 
    socketLayer->FirstStart();
    //socketLayer->NextStart();
    this->OnVoice();
}

void PKScene::OnVoice()
{
    char bgFile[10];
    sprintf(bgFile, "bg-%d.jpg", rand() % 3);
    auto background = Sprite::create(bgFile);
    this->addChild(background, -1);
    background->setScale(visibleSize.height / background->getContentSize().height);
    background->setPosition(visibleSize / 2);

    myPlayer->changeShape();
    otherPlayer->changeShape();
    myPlayer->scaleWithVoice();
    num[0] = Sprite::create("NO.1.png");
    this->addChild(num[0]);
    num[0]->setOpacity(0);
    num[0]->setPosition(visibleSize.width*0.5, visibleSize.height*0.6);
    num[1] = Sprite::create("NO.2.png");
    this->addChild(num[1]);
    num[1]->setOpacity(0);
    num[1]->setPosition(visibleSize.width*0.5, visibleSize.height*0.6);
    num[2] = Sprite::create("NO.3.png");
    this->addChild(num[2]);
    num[2]->setOpacity(0);
    num[2]->setPosition(visibleSize.width*0.5, visibleSize.height*0.6);
    this->runAction(Sequence::create(
        CallFunc::create([&]() {
        num[2]->runAction(FadeIn::create(0.3));
    }),
        DelayTime::create(1),
        CallFunc::create([&]() {
        num[2]->runAction(FadeOut::create(0.3));
        num[1]->runAction(FadeIn::create(0.3));
    }),
        DelayTime::create(1),
        CallFunc::create([&]() {
        num[1]->runAction(FadeOut::create(0.3));
        num[0]->runAction(FadeIn::create(0.3));
    }),
        DelayTime::create(1.1),
        CallFunc::create([&]() {
        num[0]->runAction(FadeOut::create(0.3));
        this->OnPK();
    }),
        NULL
        ));
}

void PKScene::OnPK()
{
    myPlayer->unschedule(schedule_selector(PlayerSprite::change));
    myPlayer->unschedule(schedule_selector(PlayerSprite::scale));
    otherPlayer->unschedule(schedule_selector(PlayerSprite::change));
    otherPlayer->unschedule(schedule_selector(PlayerSprite::scale));

    myPlayer->strength = AudioRecord::getInst()->ave_vol;
    int info = myPlayer->strength * 1000 + myPlayer->headinfo * 100 + myPlayer->bodyinfo * 10 + myPlayer->handinfo;
    int otherInfo = socketLayer->NextAtk(info);
    //int otherInfo = socketLayer->FirstAtk(info);
    otherPlayer->setInfo(otherInfo);

    myPlayer->act();
    otherPlayer->act();
    //char score[100];
    //sprintf(score, "my:%d, other:%d", myPlayer->strength, otherPlayer->strength);
    //auto text = Label::createWithTTF(score, "fonts/arial.ttf", 30);
    //this->addChild(text);
    //text->setPosition(visibleSize.width*0.5, visibleSize.height*0.5);
    this->runAction(Sequence::create(
        DelayTime::create(0.8),
        CallFunc::create([&]() {
        this->OnPKEnd(true);
        if (myPlayer->strength > otherPlayer->strength) {
            this->OnPKEnd(true);
        }
        else {
            this->OnPKEnd(false);
        }
    }),
        NULL
        ));
}

void PKScene::OnPKEnd(bool isWin)
{
    Sprite *result = nullptr;
    char wordFile[30];
    if (isWin) {
        result = Sprite::create("Win.png");
        wordFile[0] = '\0';
        sprintf(wordFile, "Win/%d.png", rand() % 7 + 1);
    }
    else {
        result = Sprite::create("Lose.png");
        wordFile[0] = '\0';
        sprintf(wordFile, "Lose/%d.png", rand() % 7 + 1);
    }
    this->addChild(result);
    result->setPosition(visibleSize.width*0.5, visibleSize.height*0.6);
    result->setScale(0.05);
    result->runAction(Spawn::create(
        FadeIn::create(0.3),
        ScaleTo::create(0.5, 1.25),
        NULL
        ));

    auto text = Sprite::create(wordFile);
    this->addChild(text);
    text->setPosition(visibleSize.width*0.5, visibleSize.height*0.6);

    auto btnHome = ButtonSprite::create("Home-0.png", "Home-1.png");
    this->addChild(btnHome);
    btnHome->setPosition(visibleSize.width*0.25, visibleSize.height*0.3);
    btnHome->setCallbackFunc([&]() {
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, StartScene::create()));
    });
    auto btnAdd = ButtonSprite::create("Add-0.png", "Add-1.png");
    this->addChild(btnAdd);
    btnAdd->setPosition(visibleSize.width*0.75, visibleSize.height*0.3);
    btnAdd->setCallbackFunc([&]() {
        Director::getInstance()->replaceScene(TransitionFade::create(0.5, FriendListScene::create()));
    });
}
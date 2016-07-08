#include "GameLayer.h"

#include "Armers/BossArmer.h"
#include "Armers/SimpleArmer.h"
#include "Armers/SmartArmer.h"
#include "Armers/SideArmer.h"

#include "EnemyWeapons/NoWeapon.h"
#include "EnemyWeapons/BossWeapon.h"
#include "EnemyWeapons/BulletWeapon.h"

#include "PlayerWeapons/OneBullet.h"
#include "PlayerWeapons/DoubleBullet.h"

GameLayer::GameLayer() {}

GameLayer::~GameLayer()
{
	SimpleAudioEngine::end();
}

bool GameLayer::init()
{
	if (!Layer::init())
		return false;

	visibleSize = Director::getInstance()->getVisibleSize();

	srand(unsigned(time(0)));

	gamelevel = 0;
	weaponChanged = false;
	playerWeaponLevel = 1;
	bonusApeared = false;
	// 击中敌机
	needUpdateScore = false;
	shotScore = 0;
	// 游戏结果
	isWin = false;
	isOver = false;

	// 爆炸动画
	Animation *animation = Animation::create();
	for (int i = 0; i != 8; i++)
	{
		char img[100] = { 0 };
		sprintf(img, "explosion/bang0%d.png", i);
		animation->addSpriteFrameWithFile(img);
	}
	animation->setDelayPerUnit(0.7f / 8);
	// 动画执行后还原初始状态
	animation->setRestoreOriginalFrame(true);
	// 将动画家加入缓存
	AnimationCache::getInstance()->addAnimation(animation, "EXPLOSION");

	// 加载音效
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/bgm.mp3");
	SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0);
	SimpleAudioEngine::getInstance()->preloadEffect("sound/shoot.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/hit.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/explosion.ogg");
	SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);

	// 创建飞机精灵
	player = PlayerSprite::create();
	deltax = 0;
	deltay = 0;
	this->addChild(player);

	return true;
}

void GameLayer::onEnter()
{
	Layer::onEnter();
	// 注册点击响应事件
	auto touchListener = EventListenerTouchOneByOne::create();
	//不向下传递触摸事件
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	touchListener->onTouchCancelled =
			CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
	//飞机精灵注册触摸事件
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	// Sound
	playMusic();
	// 创建敌人
	createEnemy(GameBarrier::getEnemys(gamelevel));
	// 创建奖励
	this->runAction(Sequence::create(
			DelayTime::create(3),
			CallFunc::create(this, callfunc_selector(GameLayer::createBonus)),
			NULL));
	// 定时升级难度
	this->runAction(Sequence::create(
			DelayTime::create(12), CallFunc::create([&](){
					this->gamelevel++;
					log("__________________ gamelevel:%d",getGameLevel());
					createEnemy(GameBarrier::getEnemys(gamelevel));
					auto text = FloatingTextSprite::create();
					text->setText("LEVEL UP");
					text->start();
					this->addChild(text);
					}),
			DelayTime::create(20), CallFunc::create([&](){
					this->gamelevel++;
					log("__________________ gamelevel:%d",getGameLevel());
					createEnemy(GameBarrier::getEnemys(gamelevel));
					auto text = FloatingTextSprite::create();
					text->setText("LEVEL UP");
					text->start();
					this->addChild(text);
					}),
			DelayTime::create(20), CallFunc::create([&](){
					this->gamelevel++;
					log("__________________ gamelevel:%d",getGameLevel());
					createEnemy(GameBarrier::getEnemys(gamelevel));
					auto text = FloatingTextSprite::create();
					text->setText("LEVEL UP");
					text->start();
					this->addChild(text);
					}),
			DelayTime::create(23), CallFunc::create([&](){
					this->gamelevel++;
					log("__________________ gamelevel:%d",getGameLevel());
					createEnemy(GameBarrier::getEnemys(gamelevel));
					auto text = FloatingTextSprite::create();
					text->setText("BOSS!!!");
					text->start();
					this->addChild(text);
					}),
			NULL));

	this->scheduleUpdate();
}

void GameLayer::update(float dt)
{
	// 碰撞检测
	this->collision();
	// 当加载的动画太多时进行清除
	if(AnimationSprite.size() > 20)
	{
		this->removeChild(AnimationSprite.at(0), true);
		AnimationSprite.erase(0);
	}
	//PlayerWeapon
	if(weaponChanged)
	{
		weaponChanged = false;
		switch(playerWeaponLevel)
		{
		case 1:
		{
			player->changeWeapon(OneBullet::create("bullet.png"));
			break;
		}
		case 2:
		{
			player->changeWeapon(DoubleBullet::create("bullet.png"));
			break;
		}
		default:
			break;
		}
	}
}

void GameLayer::createEnemy(std::vector<myEnemy> v)
{
	float intervals = 0.0;
	for(int i = 0; i != v.size(); i++)
	{
		intervals += v[i].interval;
		int type = v[i].type;
		Point startPoint = v[i].start;

		this->runAction(Sequence::create(
				DelayTime::create(intervals),
				CallFunc::create([&, type, startPoint](){
						EnemySprite* enemy = NULL;
						switch(type)
						{
						case 1:
						{
							enemy = EnemySprite::create(SimpleArmer::create("plane/enemy_1.png"), NoWeapon::create());
							enemy->setArmerPosition(startPoint);
							break;
						}
						case 2:
						{
							enemy = EnemySprite::create(SmartArmer::create("plane/enemy_2.png"), BulletWeapon::create("bullet_2.png"));
							enemy->setArmerPosition(startPoint);
							break;
						}
						case 3:
						{
							enemy = EnemySprite::create(SideArmer::create("plane/enemy_2.png"), BulletWeapon::create("bullet_2.png"));
							enemy->setArmerPosition(startPoint);
							break;
						}
						case 4:
						{
							enemy = EnemySprite::create(BossArmer::create(), BossWeapon::create());
							enemy->setArmerPosition(startPoint);
							break;
						}
						default:
						{
							log("some error occurred when creating enemys");
							enemy = EnemySprite::create(SimpleArmer::create("plane/enemy_1.png"), BulletWeapon::create("bullet_2.png"));
							enemy->setArmerPosition(startPoint);
							break;
						}
						}
						enemys.pushBack(enemy);
						this->addChild(enemy);
						enemy->start();

					}),
				NULL));
	}
}

void GameLayer::removeEnemy(EnemySprite *pEnemy)
{
	pEnemy->destroyArmer();
}

void GameLayer::createBonus()
{
	bonus = BonusSprite::create("bonus.png");
	this->addChild(bonus);

	bonusApeared = true;
	bonus->setSpeed(2.5);
	bonus->setDelayTime(0.2);
	bonus->start();

	// 如果5sec内没有获得奖励，则移除
	this->runAction(Sequence::create(
			DelayTime::create(8),
			CallFunc::create([&]()
					{
					if(bonusApeared)
						{
						playAnimation(bonus->getPosition());
						removeBonus(bonus);
						// 再次加入bonus
						this->runAction(Sequence::create(
								DelayTime::create(std::rand()%5 + 8),
								CallFunc::create(this, callfunc_selector(GameLayer::createBonus)),
								NULL));
						}
					}),
			NULL));
}

void GameLayer::removeBonus(BonusSprite *pBonus)
{
	bonusApeared = false;
	pBonus->removeFromParentAndCleanup(true);
}

// 碰撞检测
void GameLayer::collision()
{
	// 若子弹击中敌人
	for(int i = 0; i < enemys.size(); i++)
	{
		EnemySprite* enemy = enemys.at(i);
		if(!enemy->isArmerDestroyed() && player->isWeaponHit(enemy->getArmerRect()))
		{
			SimpleAudioEngine::getInstance()->playEffect("sound/hit.mp3", false);
			// 闲着没事，给每次命中加点分吧
			needUpdateScore = true;
			shotScore += 20;
			if(enemy->getArmerLife() == 1)
			{
				needUpdateScore = true;
				shotScore += enemy->getArmerScore();

				// the one who has so much score must be the Boss~~
				if(enemy->getArmerScore() == 50000)
				{
					playAnimation(enemy->getArmerPosition());
					playAnimation(enemy->getArmerPosition()-Point(enemy->getArmerSize().width, 0));
					playAnimation(enemy->getArmerPosition()+Point(enemy->getArmerSize().width, 0));
					playAnimation(enemy->getArmerPosition()-Point(0, enemy->getArmerSize().height));
					playAnimation(enemy->getArmerPosition()+Point(0, enemy->getArmerSize().height));

					this->removeEnemy(enemy);
					GameWin();
				}
				else
				{
					playAnimation(enemy->getArmerPosition());
					this->removeEnemy(enemy);
					i--;
				}
			}
			else
				enemy->setArmerLife(enemy->getArmerLife() - 1);
			break;
		}
	}

	// 如果获得奖励
	if(bonusApeared && bonus->getRect().intersectsRect(player->getPlaneRect()))
	{
		removeBonus(bonus);
		playerWeaponLevel = 2;
		weaponChanged = true;
		// 一定时间后取消bonus效果
		this->runAction(Sequence::create(
				DelayTime::create(12),
				CallFunc::create([&](){playerWeaponLevel = 1; weaponChanged = true;}),
				NULL));
		// 取消后再次加入bonus
		this->runAction(Sequence::create(
				DelayTime::create(std::rand()%5 + 12),
				CallFunc::create(this, callfunc_selector(GameLayer::createBonus)),
				NULL));
	}

	// 主角被击中
	for (int j = 0; j < enemys.size();)
	{
		EnemySprite* enemy = enemys.at(j);
		if(!enemy->isArmerDestroyed() && enemy->getArmerRect().intersectsRect(player->getPlaneRect()))
		{
			playAnimation(enemy->getArmerPosition());
			this->removeEnemy(enemy);
			GameOver();
		}
		else if(enemy->getWeapon()->isHit(player->getPlaneRect()))
		{
			GameOver();
		}
		else
			j++;
	}
}

void GameLayer::playAnimation(Point Position)
{
	auto sprite = Sprite::create();
	AnimationSprite.pushBack(sprite);
	this->addChild(sprite);
	sprite->setPosition(Position);
	sprite->runAction(Repeat::create(Animate::create(AnimationCache::getInstance()->getAnimation("EXPLOSION")), 1));
}

void GameLayer::GameWin()
{
	for(int i = 0; i != 7; i++)
	{
		playAnimation(Point(visibleSize.width/20 * (rand()%20 + 3),
				visibleSize.height*0.75 + visibleSize.height/80 * (rand()%20)));
	}

	SimpleAudioEngine::getInstance()->playEffect("sound/explosion.ogg", false);
	unscheduleUpdate();

	// GameWin
	this->runAction(Sequence::create(
			DelayTime::create(5),
			CallFunc::create([&](){isWin=true;}),
			NULL));
}

void GameLayer::GameOver()
{
	playAnimation(player->getPlanePosition());

	// 游戏结束
	SimpleAudioEngine::getInstance()->playEffect("sound/explosion.ogg", false);
	unscheduleUpdate();
	player->DestroyPlane();
	// GameOver
	this->runAction(Sequence::create(
			DelayTime::create(2),
			CallFunc::create([&](){isOver=true;}),
			NULL));
}

/*
 * 触摸事件
 */
bool GameLayer::onTouchBegan(Touch* touch, Event* pEvent)
{
	auto planePos = player->getPlanePosition();
	auto touchPos = touch->getLocation();
	deltax = touchPos.x - planePos.x;
	deltay = touchPos.y - planePos.y;
	return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event *pEvent)
{
	if(!Director::getInstance()->isPaused())
	{
		auto touchPos = touch->getLocation();
		Vec2 newPos;
		newPos.set(touchPos.x - deltax, touchPos.y - deltay);
		// 如果移动超出屏幕，限制其范围
		if (newPos.x - origin.x < 0.0)
			newPos.set(origin.x, newPos.y);
		if (newPos.x - origin.x > visibleSize.width)
			newPos.set(origin.x + visibleSize.width, newPos.y);
		if (newPos.y - origin.y < 0.0)
			newPos.set(newPos.x, origin.y);
		if (newPos.y - origin.y > visibleSize.height)
			newPos.set(newPos.x, origin.y + visibleSize.height);
		// 设置飞机新位置
		player->setPlanePosition(newPos);
	}
}

void GameLayer::onTouchEnded(Touch* touch, Event* pEvent) {

}

void GameLayer::onTouchCancelled(Touch* touch, Event* pEvent) {

}

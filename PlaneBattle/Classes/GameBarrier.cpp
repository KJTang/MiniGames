#include "GameBarrier.h"

std::vector<myEnemy> GameBarrier::getEnemys(int gamelevel)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	std::vector<myEnemy> enemys;

	switch(gamelevel)
	{
	case 0:
	{
		log("barrier 0");
		enemys.push_back({1.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.5, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.5, Point(visibleSize.width*0.85, visibleSize.height), 2});

		enemys.push_back({0.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});

		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.5, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.5, Point(visibleSize.width*0.85, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		break;
	}
	case 1:
	{
		log("barrier 1");
		enemys.push_back({1.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.5, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});

		enemys.push_back({1.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({0.5, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.85, visibleSize.height), 2});

		enemys.push_back({0.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({0.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});

		enemys.push_back({1.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({0.5, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.85, visibleSize.height), 2});

		enemys.push_back({0.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({0.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});

		enemys.push_back({1.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.5, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({1.5, Point(visibleSize.width*0.85, visibleSize.height), 2});
		break;
	}
	case 2:
	{
		log("barrier 2");
		enemys.push_back({0.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({0.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.85, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({0.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});

		enemys.push_back({1.5, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});
		enemys.push_back({1.5, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});
		enemys.push_back({1.5, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});

		enemys.push_back({0.5, Point(visibleSize.width*0.35, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.65, visibleSize.height), 1});
		enemys.push_back({0.5, Point(visibleSize.width*0.35, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.85, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.65, visibleSize.height), 1});
		enemys.push_back({0.5, Point(visibleSize.width*0.35, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.65, visibleSize.height), 1});

		enemys.push_back({1.0, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});
		enemys.push_back({1.0, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});
		enemys.push_back({1.0, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});

		enemys.push_back({1.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.85, visibleSize.height), 2});
		enemys.push_back({1.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({0.5, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.0, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});
		enemys.push_back({1.0, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});

		break;
	}
	case 3:
	{
		log("barrier 3");
		enemys.push_back({1.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.0, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.85, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.0, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.85, visibleSize.height), 2});

		enemys.push_back({1.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.0, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.85, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.0, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({0.0, Point(visibleSize.width*0.85, visibleSize.height), 2});

		enemys.push_back({1.5, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});
		enemys.push_back({1.5, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});

		enemys.push_back({1.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.0, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});
		enemys.push_back({1.0, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({1.0, Point(visibleSize.width*0.85, visibleSize.height), 2});

		enemys.push_back({1.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.0, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});
		enemys.push_back({1.0, Point(visibleSize.width*0.15, visibleSize.height), 2});
		enemys.push_back({1.0, Point(visibleSize.width*0.85, visibleSize.height), 2});

		break;
	}
	case 4:
	{
		log("barrier 4");
		enemys.push_back({1.0, Point(-1, -1), 4}); // Point(-1,-1) means use default point

		// add some wing plane, u know, the boss is not that simple :)
		enemys.push_back({15.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});

		enemys.push_back({10.0, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});

		enemys.push_back({10.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});

		enemys.push_back({10.0, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});
		enemys.push_back({2.0, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});

		enemys.push_back({10.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});

		enemys.push_back({10.0, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});
		enemys.push_back({2.0, Point(0, visibleSize.height*1.0), 3});
		enemys.push_back({0.0, Point(visibleSize.width, visibleSize.height*1.0), 3});

		enemys.push_back({10.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		enemys.push_back({1.0, Point(visibleSize.width*0.25, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.50, visibleSize.height), 1});
		enemys.push_back({0.0, Point(visibleSize.width*0.75, visibleSize.height), 1});
		break;
	}
	}

	return enemys;
}

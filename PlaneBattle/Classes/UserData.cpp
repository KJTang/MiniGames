#include "UserData.h"

using namespace cocos2d;

UserData::UserData()
{

}

void UserData::addData(std::string name, int score)
{
	for(int i = 0; i != 5; i++)
	{
		if(UserDefault::getInstance()->getIntegerForKey(rank[i], 0) < score)
		{
			int temp_score = UserDefault::getInstance()->getIntegerForKey(rank[i], 0);
//			std::string temp_name = UserDefault::getInstance()->getStringForKey(rank[i], "default");
//			UserDefault::getInstance()->setStringForKey(rank[i], name);
			UserDefault::getInstance()->setIntegerForKey(rank[i], score);
//			name = temp_name;
			score = temp_score;
		}
	}
	return;
}

std::string UserData::getDataName(int flag)
{
//	return UserDefault::getInstance()->getStringForKey(rank[flag-1], "default");
//	return "Default";
	switch(flag)
	{
	case 1:
		return "  1.   ";
	case 2:
		return "  2.   ";
	case 3:
		return "  3.   ";
	case 4:
		return "  4.   ";
	case 5:
		return "  5.   ";
	}
}

std::string UserData::getDataScore(int flag)
{
	int temp_score = UserDefault::getInstance()->getIntegerForKey(rank[flag-1], 0);
	std::string str_score;
	while(temp_score)
	{
		char c = temp_score%10 + 48;
		str_score += c;
		temp_score /= 10;
	}
	for(int i = str_score.size(); i < 8; i++)
	{
		str_score += '0';
	}
	std::reverse(str_score.begin(), str_score.end());
	return str_score;
}

void UserData::clearData()
{
	for(int i = 0; i != 5; i++)
	{
		UserDefault::getInstance()->setIntegerForKey(rank[i], 0);
//		UserDefault::getInstance()->setStringForKey(rank[i], "default");
	}
}

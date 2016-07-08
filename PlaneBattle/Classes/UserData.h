#pragma once

#include "cocos2d.h"
#include <string>

const static char rank[5][10] = {"1st","2nd","3rd","4th","5th"};

class UserData
{
private:
public:
	UserData();
	static void addData(std::string name, int score);
	static std::string getDataName(int flag);
	static std::string getDataScore(int flag);
	static void clearData();
};

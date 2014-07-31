#pragma once

#include "cocos2d.h"
#include "ActionSprite.h"

using namespace cocos2d;

class Robot : public ActionSprite
{
public:
	Robot();
	~Robot();

	bool init();
	CREATE_FUNC(Robot);
};


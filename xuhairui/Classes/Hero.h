#include "cocos2d.h"
#include "Defines.h"
#include "GameLayer.h"
#ifndef  __HERO__
#define __HERO__


USING_NS_CC;
class Hero :public Sprite
{
public:
	Hero();
	//void idle();
	//void walk(WalkDirection herodirection);
	virtual bool init() override;

	std::function<void(cocos2d::Point, float)> walk;
	std::function<void(void)> idle;
	void Runwalkaction();
	void Runidleaction();
	CREATE_FUNC(Hero);
	
	CC_SYNTHESIZE(int, walkSpeed, WalkSpeed);
	CC_SYNTHESIZE(int, runSpeed, RunSpeed);
	CC_SYNTHESIZE(float, centerToBottom, centerToBottom);
	CC_SYNTHESIZE(float, centerToSides, centerToSides);
	CC_SYNTHESIZE(Vec2, DirectionX, DirectionX);
	CC_SYNTHESIZE(ActionState,heroState,HeroState);
	CC_SYNTHESIZE(WalkDirection, herodirection, HeroDirection);
	//CC_SYNTHESIZE(Point,NextPositon,NextPosition)
};
#endif // ! __HERO__
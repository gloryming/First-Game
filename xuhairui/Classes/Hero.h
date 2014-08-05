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
	std::function<void(void)> jump;
	void Runwalkaction();
	void Runidleaction();
	void Runrunaction();
	void Runjumpaction();
	void Runjumpacctackaction();
	void Runattack_00_action();
	void Runattack_01_action();
	void Runattack_02_action();
	void Runrunattackaction();
	//void update(float dt);
	void updateHerostate(ActionState);
	CREATE_FUNC(Hero);
	CC_SYNTHESIZE(int, jumptimes, Jumptimes);
	CC_SYNTHESIZE(int, attacktimes, Attacktimes);
	CC_SYNTHESIZE(int, walkSpeed, WalkSpeed);
	CC_SYNTHESIZE(int, runSpeed, RunSpeed);
	CC_SYNTHESIZE(float, centerToBottom, centerToBottom);
	CC_SYNTHESIZE(float, centerToSides, centerToSides);
	CC_SYNTHESIZE(Vec2, DirectionX, DirectionX);
	CC_SYNTHESIZE(ActionState,heroState,HeroState);
	CC_SYNTHESIZE(ActionState, lastHeroState, LastHeroState);
	CC_SYNTHESIZE(WalkDirection, herodirection, HeroDirection);
	CC_SYNTHESIZE(Point, heroposition, Heroposition);
	//CC_SYNTHESIZE(Point,NextPositon,NextPosition)
};
#endif // ! __HERO__
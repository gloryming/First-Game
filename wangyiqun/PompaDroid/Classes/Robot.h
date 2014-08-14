#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "cocos2d.h"
#include "Character.h"

typedef enum{
	ROBOT_IDLE=0,
	ROBOT_WANDER,
	ROBOT_ATTACK,
	ROBOT_PURSUE
}RobotState;
class Robot :public Character
{
public:
	Robot();
	~Robot();
	bool init();
	CREATE_FUNC(Robot);
	CC_SYNTHESIZE(cocos2d::Point, m_moveDirection, MoveDirection);
	CC_SYNTHESIZE(float, m_catchArea, CatchArea);
	CC_SYNTHESIZE(float, m_attackArea, AttackArea);
	CC_SYNTHESIZE(RobotState, m_robotState, RobotState);
	void execute(const cocos2d::Point& target, float targetBodyWidth);
private:
	void judge(const cocos2d::Point& target, float targetBodyWidth);
	unsigned int m_nextJudgementTime;



};

#endif//_ROBOT_H_
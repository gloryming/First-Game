#pragma once
#include "cocos2d.h"

typedef enum _ActionState {
	kActionStateNone = 0,
	kActionStateIdle,
	kActionStateAttack,
	kActionStateWalk,
	kActionStateHurt,
	kActionStateKnockedOut,
	kActionStateRun,
	kActionStateJump,
	kActionStateJumpattack,
	kActionStateRunattack
} ActionState;

typedef enum _WalkDirection{
	None=0,
	Down,
	DownLeft,
	DownRight,
	Up,
	UpLeft,
	UpRight,
	Left,
	Right
}WalkDirection;

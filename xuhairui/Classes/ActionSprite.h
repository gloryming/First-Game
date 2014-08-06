#ifndef __ACTION_SPRITE__
#define __ACTION_SPRITE__
#include "cocos2d.h"
USING_NS_CC;

class ActionSprite:public Sprite
{
public:
	static Animation*  animationWithPrefix(std::string prefix, int startFrameIdx, int frameCount, float delay);
	static bool initWithSpriteFrameName(std::string photoName); 
};
#endif
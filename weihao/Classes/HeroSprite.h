#ifndef __HERO_SPRITE_H__
#define __HERO_SPRITE_H__

#include "cocos2d.h"
#include "ActionSprite.h"
USING_NS_CC;

class Hero : public ActionSprite
{
public:
	Hero();
	~Hero();
	virtual bool init() override;
	CREATE_FUNC(Hero);

private:

};

#endif
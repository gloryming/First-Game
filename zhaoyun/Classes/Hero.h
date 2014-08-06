#ifndef Philon_cocos2dx_PompaDroid_HERO_H_
#define Philon_cocos2dx_PompaDroid_HERO_H_
#pragma once

#include "ActionSprite.h"
#include "cocos2d.h"
USING_NS_CC;

class Hero : public ActionSprite
{
public:
    Hero();
    ~Hero();

    virtual bool init() override;
    CREATE_FUNC(Hero);
};

#endif // End of Philon_cocos2dx_PompaDroid_HERO_H_

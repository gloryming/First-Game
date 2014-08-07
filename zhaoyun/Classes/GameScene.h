#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

#include <cocos2d.h>
#include "GameLayer.h"
#include "OptionLayer.h"
#include "Hero.h"


class GameScene : public Scene
{
public:
    GameScene();
    ~GameScene();

    virtual bool init();
    CREATE_FUNC(GameScene);

    CC_SYNTHESIZE(GameLayer*, _gameLayer, GameLayer);
    CC_SYNTHESIZE(OptionLayer*, _optionLayer, OptionLayer);
};

#endif // End of Philon_cocos2dx_PompaDroid_GAMESCENE_H_

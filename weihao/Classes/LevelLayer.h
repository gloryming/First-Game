#ifndef __LEVEL_LAYER_H__
#define __LEVEL_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class Level : public Layer
{
public:
	Level();
	~Level();
	static Scene* createScene();
	virtual bool init() override;
	CREATE_FUNC(Level);
	CC_SYNTHESIZE_RETAIN(TMXTiledMap*, _map, map);
	CC_SYNTHESIZE_RETAIN(TMXLayer*, _tiledMap, tiledMap);

private:

};

#endif

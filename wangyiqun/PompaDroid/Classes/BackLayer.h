#ifndef __BACK_LAYER_H__
#define __BACK_LAYER_H__

#include "cocos2d.h"
#include "Hero.h"

class BackLayer: public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	BackLayer();
	~BackLayer();
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
//	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(BackLayer);
	cocos2d::TMXTiledMap* m_TiledMap;

	CC_SYNTHESIZE(cocos2d::Point, m_velocity, Velocity);
	CC_SYNTHESIZE_READONLY(Hero*, m_hero, Hero);

	void onHeroWalk(cocos2d::Point direction, float distance);
	void onHeroAttack();
	void onHeroStop();
	void update(float dt);
	void updateHero(float dt);

	float m_tileWidth;
	float m_tileHeight;

	float m_screenWidth;
	float m_screenHeight;
	cocos2d::Point m_origin;
	cocos2d::SpriteBatchNode *m_spriteNodes;
};

#endif // __PLAY_SCENE_H__

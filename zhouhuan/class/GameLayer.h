#pragma once
#include "cocos2d.h"

class BaseSprite;
class Hero;
class GameLayer : public cocos2d::Layer
{
public:
	GameLayer(void);
	~GameLayer(void);

	virtual bool init();

	void onHeroWalk(cocos2d::Point direction, float distance);
	void onHeroStop();
	//void onHeroAttack();

	CC_SYNTHESIZE_READONLY(Hero*, m_pHero, Hero);

	void initTiledMap ();
	cocos2d::TMXTiledMap* _tileMap;
	//cocos2d::SpriteBatchNode* _actors;

	float m_fScreenWidth;
	float m_fScreenHeight;
	cocos2d::Point m_origin;

	cocos2d::SpriteBatchNode *m_pSpriteNodes;
	CREATE_FUNC(GameLayer);

	
 
		
//private:
	//cocos2d::TMXTiledMap *m_pTiledMap;
};

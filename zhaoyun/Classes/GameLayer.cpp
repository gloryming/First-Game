#include "GameLayer.h"
#include "GameScene.h"
USING_NS_CC;


GameLayer::GameLayer(void)
{
	map = NULL;
}

GameLayer::~GameLayer(void)
{
}

bool GameLayer::init(){
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		map = TMXTiledMap::create("pd_tilemap.tmx");
		
		this->addChild(map,-10);

		bRet = true;
	} while (0);
	return bRet;
}

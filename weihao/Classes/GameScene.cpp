#include "GameScene.h"
#include "LevelLayer.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Scene::init());

		_level = Level::create();
		this->addChild(_level, 0);
		_hudLayer = HudLayer::create();
		this->addChild(_hudLayer, 1);
		_hudLayer->getDPad()->setDelegate(_level);

		bRet = true;
	} while (0);

	return bRet;
}

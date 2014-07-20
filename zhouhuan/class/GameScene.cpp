#include"GameScene.h"
//#include"OperateLayer.h"
//#include "GameLayer.h"
//#include "OperateLayer.h"

USING_NS_CC;

GameScene::GameScene(void )
{
	this->_gameLayer = NULL;
	this->_operate = NULL;
}

GameScene::~GameScene(void )
{

}

bool GameScene::init()
{
	if(!Scene::init())
	{
		return false;
	}
	_gameLayer = GameLayer ::create(); 
	this->addChild (_gameLayer,0);

	_operate = OperateLayer::create();
	this->addChild(_operate, 1);
	_operate->setHero(_gameLayer->getHero());
	return true;
}
/*Scene* GameScene::createScene()
{
 auto scene = Scene::create();
 
 auto gameLayer = GameLayer::create();
 scene->addChild(gameLayer, 0);
 return scene;
}*/
/*Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	/*auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

	auto gameLayer=GameLayer::create();
	scene->addChild(gameLayer,0);

	auto operateLayer=OperateLayer::create();
	scene->addChild(operateLayer,1);
	operateLayer->setHero(gameLayer->getHero());
    // return the scene
    return scene;
}*/
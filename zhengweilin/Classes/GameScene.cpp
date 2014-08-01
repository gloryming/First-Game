#pragma once
#include "GameScene.h"


GameScene::GameScene()
{

}


GameScene::~GameScene()
{

}

bool GameScene::init(){
	bool ret = false;

	do{
		CC_BREAK_IF(!Scene::init());

		_gameLayer = GameLayer::create();
		this->addChild(_gameLayer, 0);

		ret = true;
	} while (0);

	return ret;
}


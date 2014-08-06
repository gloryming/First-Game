#pragma once
#include "GameScene.h"
#include "OperationLayer.h"

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
		
		_operationLayer = OperationLayer::create();
		_operationLayer->setDelegator(_gameLayer);
		this->addChild(_operationLayer);
	
		ret = true;
	} while (0);

	return ret;
}


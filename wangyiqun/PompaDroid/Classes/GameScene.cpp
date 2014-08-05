#include "GameScene.h"
#include "BackLayer.h"
#include "OperateLayer.h"
USING_NS_CC;

Scene* GameScene::createScene(){
	auto scene = Scene::create();
	
	auto backLayer = BackLayer::create();	
	scene->addChild(backLayer, 0);

	auto operateLayer = OperateLayer::create();
	scene->addChild(operateLayer, 10);
	operateLayer->setHero(backLayer->getHero());

	return scene;
}
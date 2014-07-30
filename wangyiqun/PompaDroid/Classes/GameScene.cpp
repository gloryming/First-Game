#include "GameScene.h"
#include "BackLayer.h"
USING_NS_CC;

Scene* GameScene::createScene(){
	auto scene = Scene::create();
	auto backLayer = BackLayer::create();
	
	scene->addChild(backLayer, 0);
	return scene;
}
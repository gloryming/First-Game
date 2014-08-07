#include "GameScene.h"
#include "GameLayer.h"

using namespace cocos2d;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

bool GameScene::init()
{
    bool ret = false;

    do {
        CC_BREAK_IF(!Scene::init());

        _gameLayer = GameLayer::create();
		this->addChild(_gameLayer, 0);
        _optionLayer = OptionLayer::create();
        this->addChild(_optionLayer, 1);
		_optionLayer->getDPad()->setDelegate(_gameLayer);      
        
        ret = true;
    } while (0);
    return ret;
}

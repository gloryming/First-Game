#include "GameScene.h"
USING_NS_CC;

	GameScene::GameScene(void){
	
};


	GameScene::~GameScene(void){

	}


	bool GameScene::init(){
		bool bRet = false;
		do 
		{
			CC_BREAK_IF(!CCScene::init());

			_gameLayer = GameLayer::create();
			this->addChild(_gameLayer, 0);

			bRet = true;
		} while (0);

		return bRet;
	}

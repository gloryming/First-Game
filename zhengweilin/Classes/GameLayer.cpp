#include "GameLayer.h"
#include "ActionSprite.h"
#include "GameScene.h"

GameLayer::GameLayer()
{
}


GameLayer::~GameLayer()
{
}


bool GameLayer::init(){

	bool ret = false;
	
	do{
		CC_BREAK_IF(!Layer::init());

		_map = TMXTiledMap::create("map.tmx");
		this->addChild(_map);
	
		
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pd_sprites.plist");
		_actors = SpriteBatchNode::create("pd_sprites.pvr.ccz");
		this->addChild(_actors);
		
		_hero = Hero::create();
 		_hero->setPosition(80, 80);
		_hero->walk(Point(1, 1));
		_actors->addChild(_hero);

		_robots = Array::createWithCapacity(5);
		for (int i = 0; i < 5; i++){
			Robot* robot = Robot::create();
			robot->setPosition(rand() % 400 + 80, rand() % 100);
			robot->idle();
			_robots->addObject(robot);
			_actors->addChild(robot);
		}
	//	auto sp = Hero::create();
	////	sp->idle();
	//	sp->setPosition(80, 80);
	//	_actors->addChild(sp);

		//Sprite* sp = Sprite::create("hero_walk_00.png");
		//sp->setPosition(80, 80);
		//this->addChild(sp);

		//auto animation1 = Animation::create();

		//auto sfc = SpriteFrameCache::getInstance();
		//

		//animation1->addSpriteFrame(sfc->getSpriteFrameByName("hero_idle_00.png"));
		//animation1->addSpriteFrame(sfc->getSpriteFrameByName("hero_idle_01.png"));
		//animation1->addSpriteFrame(sfc->getSpriteFrameByName("hero_idle_02.png"));
		//animation1->addSpriteFrame(sfc->getSpriteFrameByName("hero_idle_03.png"));
		//animation1->addSpriteFrame(sfc->getSpriteFrameByName("hero_idle_04.png"));
		//animation1->addSpriteFrame(sfc->getSpriteFrameByName("hero_idle_05.png"));

		//animation1->setDelayPerUnit(1.0f / 6.0f);
		//animation1->setRestoreOriginalFrame(true);
		//auto action = Animate::create(animation1);
		//auto sp = Sprite::create();

		//this->addChild(sp);
		//
		//sp->setPosition(80, 80);
		//sp->runAction(RepeatForever::create(action));

		//Sprite* sp = Sprite::create("Hero/hero_idle_00.png");
		//sp->setPosition(80, 80);
		//this->addChild(sp);


		ret = true;
	} while (0);

	return ret;
}
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
		_hero->setZOrder(80);
		_hero->walk(Point(1, 1));
		_actors->addChild(_hero);

		_robots = Array::createWithCapacity(5);
		for (int i = 0; i < 5; i++){
			Robot* robot = Robot::create();
			robot->setPosition(rand() % 400 + 80, rand() % 100);
			robot->setZOrder(100 - robot->getPosition().y);
			robot->idle();
			_robots->addObject(robot);
			_actors->addChild(robot);

		}

		ret = true;
	} while (0);

	return ret;
}

void GameLayer::onAttack(){
	_hero->attack();
}

void GameLayer::onWalk(Point direction, float distance){
	direction *= 2;
	_hero->walk(direction);
	if (_hero->getPosition().x > width * 0.75 && direction.x > 0){
		this->_map->setPosition(_map->getPosition() - Point(direction.x, 0));
		_hero->setPosition(_hero->getPosition() + Point(0, direction.y));
		
	}
	else if (_hero->getPosition().x < width * 0.25 && direction.x < 0){
		this->_map->setPosition(_map->getPosition() - Point(direction.x, 0));
		_hero->setPosition(_hero->getPosition() + Point(0, direction.y));
	}
	else{
		_hero->setPosition(_hero->getPosition() + direction);
	}
}

void GameLayer::onStop(){
	_hero->idle();
}
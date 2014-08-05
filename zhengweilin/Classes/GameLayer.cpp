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
	
		
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Hero.plist");
		_actors = SpriteBatchNode::create("Hero.png");
		this->addChild(_actors);
		
		_hero = Hero::create();
 		_hero->setPosition(80, 80);
		_hero->setZOrder(80);
		_hero->walk(Point(1, 1));
		_actors->addChild(_hero);

		//_robots = Array::createWithCapacity(5);
		//for (int i = 0; i < 5; i++){
		//	Robot* robot = Robot::create();
		//	robot->setPosition(rand() % 400 + 80, rand() % 100);
		//	robot->setZOrder(100 - robot->getPosition().y);
		//	robot->idle();
		//	_robots->addObject(robot);
		//	_actors->addChild(robot);

		//}

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
	if (_hero->getPosition().y > 120){
		_hero->setPosition(Point(_hero->getPosition().x, 120));
		direction = Point(direction.x, 0);
	}
	if (_hero->getPosition().y < 40){
		_hero->setPosition(Point(_hero->getPosition().x, 40));
		direction = Point(direction.x, 0);
	}
	if (_hero->getPosition().x < 20){
		_hero->setPosition(Point(20, _hero->getPosition().y));
		direction = Point(0, direction.y);
	}
	if (_hero->getPosition().x > width - 20){
		_hero->setPosition(Point(width - 20, _hero->getPosition().y));
		direction = Point(0, direction.y);
	}
	if (_hero->getPosition().x > width * 0.66 && direction.x > 0 && _map->getPosition().x > width - 3200){
		log("_map.x = %f", _map->getPosition().x);
		this->_map->setPosition(_map->getPosition() - Point(direction.x, 0));
		_hero->setPosition(_hero->getPosition() + Point(0, direction.y));
		
	}
	else if (_hero->getPosition().x < width * 0.33 && direction.x < 0 && _map->getPosition().x < 0){
		log("_map.x = %f", _map->getPosition().x);
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
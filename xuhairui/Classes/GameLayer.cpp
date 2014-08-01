#include "GameLayer.h"
USING_NS_CC;

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->setActualWidth(0);
	auto winSize = Director::getInstance()->getWinSize();

	map = TMXTiledMap::create("MainGameScene.tmx");
	//auto bgLayer = map->getLayer("bg");
	_hero = Hero::create();
	_hero->setAnchorPoint(Point(0.5, 0.5));
	_hero->setPosition(_hero->getcenterToSides(), _hero->getcenterToBottom());
	addChild(_hero, 1);

	map->setAnchorPoint(Point(0, 0.5));
	map->setPosition(Point(0, winSize.height / 2));
	this->addChild(map, -10);

	getHero()->walk = CC_CALLBACK_2(GameLayer::Hero_walk, this);
	getHero()->idle = CC_CALLBACK_0(GameLayer::Hero_stop, this);
	scheduleUpdate();
	return true;
}

void GameLayer::update(float dt)
{
	moveBackground();
	checkstate();
}

void GameLayer::checkstate()
{

	if (getHero()->getHeroDirection() != None)
	{
		_hero->walk(getHero()->getPosition(),1.0f);
	}
	else {
		_hero->idle();
	}
}
void GameLayer::moveBackground()
{
	auto winSize = Director::getInstance()->getWinSize();
	actualWidth = MAX(_hero->getPositionX(), winSize.width / 2);
	actualWidth = MIN(actualWidth, (map->getMapSize().width*map->getTileSize().width - winSize.width / 2));
	this->setPosition(Point(-actualWidth + winSize.width / 2, 0));
}

void GameLayer::Hero_walk(Point destination, float duration){
	auto herodirection = this->getHero()->getHeroDirection();
	Point *angle;
	if (herodirection == Up)
	{
		angle = new  Point(0, 1.0);
	}
	else if (herodirection == UpLeft)
	{
		angle = new Point(-1.0, 1.0);
	}
	else if (herodirection == UpRight)
	{
		angle = new Point(1.0, 1.0);
	}
	else if (herodirection == Down)
	{
		angle = new Point(0, -1.0);
	}
	else if (herodirection == DownLeft)
	{
		angle = new Point(-1.0, -1.0);
	}
	else if (herodirection == DownRight)
	{
		angle = new Point(1.0, -1.0);
	}
	else if (herodirection == Left)
	{
		angle = new Point(-1.0, 0);
	}
	else if (herodirection == Right)
	{
		angle = new Point(1.0, 0);
	}
	angle->normalize();
	if (angle->x > 0)
		this->getHero()->setFlipX(false);
	else
		this->getHero()->setFlipX(true);
	Size size = Director::getInstance()->getWinSize();

	destination = destination + *angle*getHero()->getWalkSpeed();
	destination.x = MIN(MAX(getHero()->getcenterToSides(), destination.x ), map->getMapSize().width*map->getTileSize().width-getHero()->getcenterToSides() );
	destination.y = MIN(MAX(getHero()->getcenterToBottom(), destination.y  ), map->getTileSize().width * 6);
	this->getHero()->setPosition(destination);
	//this->getHero()->runAction(MoveTo::create(duration, destination));
}

void GameLayer::Hero_stop()
{
	this->getHero()->Runidleaction();
}
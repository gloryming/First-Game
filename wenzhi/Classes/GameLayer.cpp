#include "GameLayer.h"
#include "Hero.h"

USING_NS_CC;

GameLayer::GameLayer()
: _map(NULL)
, _hero(NULL)
, m_tileWidth(0)
, m_tileHeight(0)
{
}

GameLayer::~GameLayer()
{
}

bool GameLayer::init()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("joypad.plist");

	if (!Layer::init())
	{
		return false;
	}
	
	Size winSize = Director::getInstance()->getWinSize();

	_map = TMXTiledMap::create("tiled_map.tmx");
	_map->setAnchorPoint(Vec2(0, 0));
	_map->setPosition(Vec2::ZERO);
	this->addChild(_map);

	Size tileSize = _map->getTileSize();
	m_tileWidth = tileSize.width;
	m_tileHeight = tileSize.height;

	_hero = Hero::create();
	_hero->setPosition(Vec2(100, 100));
	_hero->toIdleAction();

	this->addChild(_hero);

	scheduleUpdate();

	return true;
}

void GameLayer::update(float dt)
{
	updateHero(dt);

	if (_hero->getRunTimer())
	{
		_hero->setRunTimer(_hero->getRunTimer() - 1);
	}

	if (_hero->getAttackTimer())
	{
		_hero->setAttackTimer(_hero->getAttackTimer() - 1);
	}
	else if (_hero->getAttackIndex())
	{
		_hero->setAttackIndex(0);
	}
}

void GameLayer::updateHero(float dt)
{
	if (_hero->getCurrentState() == ACTION_STATE_WALK || _hero->getCurrentState() == ACTION_STATE_RUN)
	{
		float halfHeroFrameHeight = (_hero->getDisplayFrame()->getRect().size.height) / 2;
		float speed;
		Vec2 endPosition;
		if (_hero->getCurrentState() == ACTION_STATE_WALK)
		{
			speed = _hero->getSpeed();
		}
		else if (_hero->getCurrentState() == ACTION_STATE_RUN)
		{
			speed = _hero->getSpeed() * 2;
		}

		switch (_hero->getDir())
		{
		case DIR_RIGHT: endPosition = Vec2(_hero->getPosition().x + speed, _hero->getPosition().y); break;
		case DIR_UPRIGHT: endPosition = Vec2(_hero->getPosition().x + speed, _hero->getPosition().y + 0.8); break;
		case DIR_DOWNRIGHT: endPosition = Vec2(_hero->getPosition().x + speed, _hero->getPosition().y - 0.8); break;
		case DIR_LEFT: endPosition = Vec2(_hero->getPosition().x + speed, _hero->getPosition().y); break;
		case DIR_UPLEFT: endPosition = Vec2(_hero->getPosition().x + speed, _hero->getPosition().y + 0.8); break;
		case DIR_DOWNLEFT: endPosition = Vec2(_hero->getPosition().x + speed, _hero->getPosition().y - 0.8); break;
		case DIR_UP: endPosition = Vec2(_hero->getPosition().x, _hero->getPosition().y + 0.8); break;
		case DIR_DOWN: endPosition = Vec2(_hero->getPosition().x, _hero->getPosition().y - 0.8); break;
		}
		Point actualPosition = endPosition;
		// can not walk on the wall or out of map
		Size winSize = Director::getInstance()->getWinSize();

		if (endPosition.y < halfHeroFrameHeight + 3 || endPosition.y >(m_tileHeight * 3 + halfHeroFrameHeight))
		{
			actualPosition.y = _hero->getPositionY();
		}

		float mapWidth = _map->getContentSize().width;
		float halfWinWidth = winSize.width / 2;
		float halfHeroFrameWidth = (_hero->getDisplayFrame()->getRect().size.width) / 2;
		// move the map
		if ((endPosition.x > halfWinWidth && endPosition.x <= (mapWidth - halfWinWidth)) && (_hero->getDir() != DIR_UP) && (_hero->getDir() != DIR_DOWN))
		{
			this->setPositionX(this->getPositionX() - speed);
		}
		else if (endPosition.x < halfHeroFrameWidth || endPosition.x >= mapWidth - halfHeroFrameWidth)
		{
			actualPosition.x = _hero->getPositionX();
		}
		_hero->setPosition(actualPosition);
		_hero->setZOrder(winSize.height - _hero->getPositionY());
	}
	else if (_hero->getCurrentState() == ACTION_STATE_JUMP)
	{
		float halfHeroFrameHeight = (_hero->getDisplayFrame()->getRect().size.height) / 2;
		float speed = _hero->getSpeed()*2.5;
		Vec2 endPosition;

		switch (_hero->getDir())
		{
		case DIR_RIGHT: endPosition = Vec2(_hero->getPosition().x + speed, _hero->getPosition().y); break;
		case DIR_UPRIGHT: endPosition = Vec2(_hero->getPosition().x + speed, _hero->getPosition().y + 0.8); break;
		case DIR_DOWNRIGHT: endPosition = Vec2(_hero->getPosition().x + speed, _hero->getPosition().y - 0.8); break;
		case DIR_LEFT: endPosition = Vec2(_hero->getPosition().x + speed, _hero->getPosition().y); break;
		case DIR_UPLEFT: endPosition = Vec2(_hero->getPosition().x + speed, _hero->getPosition().y + 0.8); break;
		case DIR_DOWNLEFT: endPosition = Vec2(_hero->getPosition().x + speed, _hero->getPosition().y - 0.8); break;
		case DIR_UP: endPosition = Vec2(_hero->getPosition().x, _hero->getPosition().y + 0.8); break;
		case DIR_DOWN: endPosition = Vec2(_hero->getPosition().x, _hero->getPosition().y - 0.8); break;
		}
		Point actualPosition = endPosition;
		// can not walk on the wall or out of map
		Size winSize = Director::getInstance()->getWinSize();

		if (endPosition.y < halfHeroFrameHeight + 3 || endPosition.y >(m_tileHeight * 3 + halfHeroFrameHeight))
		{
			actualPosition.y = _hero->getPositionY();
		}

		float mapWidth = _map->getContentSize().width;
		float halfWinWidth = winSize.width / 2;
		float halfHeroFrameWidth = (_hero->getDisplayFrame()->getRect().size.width) / 2;
		// move the map
		if ((endPosition.x > halfWinWidth && endPosition.x <= (mapWidth - halfWinWidth)) && (_hero->getDir() != DIR_UP) && (_hero->getDir() != DIR_DOWN))
		{
			this->setPositionX(this->getPositionX() - speed);
		}
		else if (endPosition.x < halfHeroFrameWidth || endPosition.x >= mapWidth - halfHeroFrameWidth)
		{
			actualPosition.x = _hero->getPositionX();
		}
		_hero->setPosition(actualPosition);
		_hero->setZOrder(winSize.height - _hero->getPositionY());
	}
}
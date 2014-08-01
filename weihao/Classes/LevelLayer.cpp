#include "LevelLayer.h"
#include"HeroSprite.h"

Level::Level()
{
	_map = NULL;
	_tiledMap = NULL;
	_hero = NULL;
}

Level::~Level()
{
}

bool Level::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();

	// init map
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		this->setmap(TMXTiledMap::create("map.tmx"));
		this->settiledMap(_map->layerNamed("tiledMap"));
		_tiledMap->setAnchorPoint(Vec2(0, 1));
		_tiledMap->setPosition(Vec2(0,winSize.height));
		this->addChild(_map, -1);
		bRet = true;
	} while (0);

	// add actors
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pd_sprites.plist");
	_actors = SpriteBatchNode::create("pd_sprites.pvr.ccz");
	_actors->getTexture()->setAliasTexParameters();
	this->addChild(_actors, 0);

	// init hero
	this->initHero();

	this->scheduleUpdate();

	return bRet;
}

void Level::initHero()
{
	_hero = Hero::create();
	_actors->addChild(_hero);
	_hero->setPosition(Vec2(_hero->getCenterToSides(), 160));
	_hero->setDesiredPosition(_hero->getPosition());
	_hero->idle();
}

void Level::update(float dt)
{
	_hero->update(dt);
	this->updatePositions();
}

void Level::updatePositions()
{
	float posX = MIN(_map->getMapSize().width * _map->getTileSize().width - _hero->getCenterToSides(),
		MAX(_hero->getCenterToSides(), _hero->getDesiredPosition().x));
	float posY = MIN(5 * _map->getTileSize().height + _hero->getCenterToBottom(),
		MAX(_hero->getCenterToBottom(), _hero->getDesiredPosition().y));
	_hero->setPosition(ccp(posX, posY));
}

void Level::didChangeDirectionTo(SimpleDPad *simpleDPad, Vec2 direction)
{
	_hero->walkWithDirection(direction);
}

void Level::isHoldingDirection(SimpleDPad *simpleDPad, Vec2 direction)
{
	_hero->walkWithDirection(direction);
}

void Level::simpleDPadTouchEnded(SimpleDPad *simpleDPad)
{
	if (_hero->getActionState() == kActionStateWalk)
	{
		_hero->idle();
	}
}
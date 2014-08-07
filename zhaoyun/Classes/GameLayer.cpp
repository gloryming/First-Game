#include "GameLayer.h"
#include "cocos2d.h"
#include "Hero.h"

GameLayer::GameLayer(){
	_map = NULL;
	_tiledMap = NULL;
	_hero = NULL;
}


GameLayer::~GameLayer()
{}

bool GameLayer::init()
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
	//_actors->getTexture()->setAliasTexParameters();
	this->addChild(_actors, 0);

	// init hero
	this->initHero();

	// add buttons
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("button.plist");
	_buttons = SpriteBatchNode::create("button.pvr.ccz");
	_buttons->getTexture()->setAliasTexParameters();
	this->addChild(_buttons);

	// init buttons
	auto _attackSprite = Sprite::createWithSpriteFrameName("button_a_normal@2x.png");
	auto _jumpSprite = Sprite::createWithSpriteFrameName("button_b_normal@2x.png");
	_attackSprite->setPosition(winSize.width - _attackSprite->getContentSize().width/2, 
		_attackSprite->getContentSize().height/2);
	_jumpSprite->setPosition(winSize.width - _jumpSprite->getContentSize().width*4/3,
		_jumpSprite->getContentSize().height*4/3);
	this->addChild(_attackSprite, 1);
	this->addChild(_jumpSprite, 1);

	// add listeners
	auto _attackListener = EventListenerTouchOneByOne::create();
	_attackListener->onTouchBegan = [&](Touch *ptouch, Event *pevent) -> bool{
		auto target = static_cast<Sprite*>(pevent->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(ptouch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			auto fram = SpriteFrameCache::getInstance()->getSpriteFrameByName("button_a_selected@2x.png");
			target->setSpriteFrame(fram);
			_hero->attack();
			return true;
		}			
		return false;
	};
	_attackListener->onTouchEnded = [&](Touch *ptouch, Event *pevent){
		auto target = static_cast<Sprite*>(pevent->getCurrentTarget());
		auto fram = SpriteFrameCache::getInstance()->getSpriteFrameByName("button_a_normal@2x.png");
		target->setSpriteFrame(fram);
		//_hero->idle();
	};
	auto _jumpListener = EventListenerTouchOneByOne::create();
	_jumpListener->onTouchBegan = [&](Touch *ptouch, Event *pevent) -> bool{
		auto target = static_cast<Sprite*>(pevent->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(ptouch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (rect.containsPoint(locationInNode))
		{
			auto fram = SpriteFrameCache::getInstance()->getSpriteFrameByName("button_b_selected@2x.png");
			target->setSpriteFrame(fram);
			_hero->jump();
			return true;
		}
		return false;
	};
	_jumpListener->onTouchEnded = [&](Touch *ptouch, Event *pevent){
		auto target = static_cast<Sprite*>(pevent->getCurrentTarget());
		auto fram = SpriteFrameCache::getInstance()->getSpriteFrameByName("button_b_normal@2x.png");
		target->setSpriteFrame(fram);
		//_hero->idle();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_attackListener, _attackSprite);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_jumpListener, _jumpSprite);


	// update
	this->scheduleUpdate();

	return bRet;
}

void GameLayer::initHero()
{
	_hero = Hero::create();
	_actors->addChild(_hero);
	_hero->setPosition(Vec2(_hero->getCenterToSides(), 160));
	_hero->setDesiredPosition(_hero->getPosition());
	_hero->idle();
}

void GameLayer::update(float dt)
{
	_hero->update(dt);
	if (_hero->getActionState() == kActionStateWalk
		|| _hero->getActionState() == kActionStateRun
		|| _hero->getActionState() == kActionStateIdle)
		this->updatePositions();
}

void GameLayer::updatePositions()
{
	float posX = MIN(_map->getMapSize().width * _map->getTileSize().width - _hero->getCenterToSides(),
		MAX(_hero->getCenterToSides(), _hero->getDesiredPosition().x));
	float posY = MIN(5 * _map->getTileSize().height + _hero->getCenterToBottom(),
		MAX(_hero->getCenterToBottom(), _hero->getDesiredPosition().y));
	_hero->setPosition(ccp(posX, posY));
}

void GameLayer::didChangeDirectionTo(SimpleDPad *simpleDPad, Vec2 direction)
{
	_hero->walkWithDirection(direction);
}

void GameLayer::isHoldingDirection(SimpleDPad *simpleDPad, Vec2 direction)
{
	if (_hero->getActionState() == kActionStateWalk)
		_hero->walkWithDirection(direction);
	if (_hero->getActionState() == kActionStateRun)
		_hero->runWithDirection(direction);
}

void GameLayer::didChangeDirectionToWithRun(SimpleDPad *simpleDPad, Vec2 direction)
{
	_hero->runWithDirection(direction);
}

void GameLayer::simpleDPadTouchEnded(SimpleDPad *simpleDPad)
{
	if (_hero->getActionState() == kActionStateWalk || _hero->getActionState() == kActionStateRun)
	{
		_hero->idle();
	}
}



// Philon 2013/10/23


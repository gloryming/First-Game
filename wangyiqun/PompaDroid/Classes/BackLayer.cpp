#include "BackLayer.h"
USING_NS_CC;

BackLayer::BackLayer() :m_TiledMap(NULL){

}

BackLayer::~BackLayer(){

}

bool BackLayer::init(){
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		m_TiledMap = TMXTiledMap::create("tiles.tmx");
		this->addChild(m_TiledMap, -5);

		auto visibleSize = Director::getInstance()->getVisibleSize();
		this->m_origin = Director::getInstance()->getVisibleOrigin();
		this->m_screenWidth = visibleSize.width;
		this->m_screenHeight = visibleSize.height;

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Hero.plist");
		m_spriteNodes = SpriteBatchNode::create("Hero.png");
		this->addChild(m_spriteNodes);

		m_hero = Hero::create();
		m_hero->setPosition(m_origin + Point(100, 100));
		m_hero->runIdleAction();
		m_hero->setZOrder(m_screenHeight - m_hero->getPositionY());
		m_spriteNodes->addChild(m_hero);

		Size tileSize = m_TiledMap->getTileSize();
		m_tileWidth = tileSize.width;
		m_tileHeight = tileSize.height;

		m_hero->attack = CC_CALLBACK_0(BackLayer::onHeroAttack, this);
		m_hero->stop = CC_CALLBACK_0(BackLayer::onHeroStop, this);
		m_hero->walk = CC_CALLBACK_2(BackLayer::onHeroWalk, this);

		this->scheduleUpdate();

		ret = true;
	} while (0);
	return ret;
}

void BackLayer::onHeroWalk(Point direction, float distance)
{
	m_hero->setFlippedX(direction.x < 0 ? true : false);
	m_hero->runWalkAction();
	Point velocity = direction * (distance < 78 ? 1 : 3);
	m_hero->setVelocity(velocity);
}

void BackLayer::onHeroAttack()
{
	m_hero->runAttackAction();
}
void BackLayer::onHeroStop()
{
	m_hero->runIdleAction();
}
void BackLayer::update(float dt)
{
	this->updateHero(dt);
}

void BackLayer::updateHero(float dt)
{
	if (m_hero->getCurActionStatus() == ACTION_WALK)
	{
		float halfHeroFrameHeight = (m_hero->getDisplayFrame()->getRect().size.height) / 2;
		Point expectP = m_hero->getPosition() + m_hero->getVelocity();
		Point actualP = expectP;

		//can not walk on the wall or out of map
		if (expectP.y < halfHeroFrameHeight || expectP.y >(m_tileHeight * 3 + halfHeroFrameHeight))
		{
			actualP.y = m_hero->getPositionY();
		}
		float mapWidth = m_TiledMap->getContentSize().width;
		float halfWinWidth = m_screenWidth / 2;
		float halfHeroFrameWidth = (m_hero->getDisplayFrame()->getRect().size.width) / 2;
		if (expectP.x > halfWinWidth && expectP.x <= (mapWidth - halfWinWidth))
		{
			this->setPositionX(this->getPositionX() - m_hero->getVelocity().x);
		}
		else if (expectP.x < halfHeroFrameWidth || expectP.x >= mapWidth - halfHeroFrameWidth)
		{
			actualP.x = m_hero->getPositionX();
		}
		m_hero->setPosition(actualP);
		m_hero->setZOrder(m_screenHeight - m_hero->getPositionY());
	}
}
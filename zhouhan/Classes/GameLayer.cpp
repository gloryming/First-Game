#include "GameLayer.h"
#include "Hero.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

bool collisionDetection(const BoundingBox &hitBox, const BoundingBox &bodyBox)
{
	Rect hitRect = hitBox.actual;
	Rect bodyRect = bodyBox.actual;
	if(hitRect.intersectsRect(bodyRect))
	{
		return true;
	}

	return false;
}


GameLayer::GameLayer()
	:m_pTiledMap(NULL),
	m_pSpriteNodes(NULL),
	m_pHero(NULL)
{

}

GameLayer::~GameLayer()
{
	
}

bool GameLayer::init()
{
	bool ret = false;
	do {
		CC_BREAK_IF( !Layer::init());

		auto visibleSize = Director::getInstance()->getVisibleSize();
		this->m_origin = Director::getInstance()->getVisibleOrigin();
		this->m_fScreenWidth = visibleSize.width;
		this->m_fScreenHeight = visibleSize.height;

		m_pTiledMap = TMXTiledMap::create("pd_tilemap.tmx");
		this->addChild(m_pTiledMap);
		Size tileSize = m_pTiledMap->getTileSize();
		m_fTileWidth = tileSize.width;
		m_fTileHeight = tileSize.height;

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pd_sprites.plist");
		m_pSpriteNodes = SpriteBatchNode::create("pd_sprites.pvr.ccz");
		this->addChild(m_pSpriteNodes);

		m_pHero = Hero::create();
		m_pHero->setPosition( m_origin + Point(100, 100) );
		m_pHero->runIdleAction();
		m_pHero->setZOrder(m_fScreenHeight - m_pHero->getPositionY());
		m_pHero->stop = CC_CALLBACK_0(GameLayer::onHeroStop, this);
		m_pHero->walk = CC_CALLBACK_2(GameLayer::onHeroWalk, this);

		

		m_pSpriteNodes->addChild(m_pHero);

		ret = true;
	} while(0);

	return ret;
}




void GameLayer::onHeroWalk(Point direction, float distance)
{
	if(m_pHero->isLive())
	{
		m_pHero->setFlippedX(direction.x < 0 ? true : false);
		m_pHero->runWalkAction();

		Point velocity = direction * (distance < 78 ? 1 : 3);
		m_pHero->setVelocity(velocity);
	}
}



void GameLayer::onHeroStop()
{
	if(m_pHero->isLive())
	{
		m_pHero->runIdleAction();
	}
}

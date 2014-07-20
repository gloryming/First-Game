#include"GameLayer.h"
#include"cocos2d.h"
#include"Hero.h"
USING_NS_CC;

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

GameLayer::GameLayer(void )
	//:m_pTiledMap(NULL)
	:m_pSpriteNodes(NULL),
	 m_pHero(NULL)
{

}

GameLayer::~GameLayer(void )
{

}

/*bool GameLayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	this->initTiledMap(); 

	return true;
}*/


/*void GameLayer::initTiledMap(){
	(TMXTiledMap*  _tileMap = TMXTiledMap::create("pd_tilemap.tmx");
	CCArray *pChildrenArray = _tileMap->getChildren();
	Object* obj = NULL;
	CCARRAY_FOREACH(_tileMap->getChildren(),obj){
		TMXLayer* _child = (TMXLayer* )obj;

		_child->getTexture()->setAliasTexParameters(); 
	}
	this->addChild(_tileMap);

	 _tileMap = TMXTiledMap::create("pd_tilemap.tmx");
	 CCArray *pChildrenArray = _tileMap->getChildren();
     
     CCObject *pObject = NULL;
     CCARRAY_FOREACH(pChildrenArray,pObject){
     
    
     child->getTexture()->setAntiAliasTexParameters();
     }*/

bool GameLayer::init(){    
	bool ret = false;    
	do {        
		CC_BREAK_IF(!Layer::init());        
		_tileMap = TMXTiledMap::create("pd_tilemap.tmx");        
		this->addChild(_tileMap);

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
	
		m_pHero->walk = CC_CALLBACK_2(GameLayer::onHeroWalk, this);

		ret = true;
        } while(0);  
	/*SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("pd_sprites.plist");
    _actors=SpriteBatchNode::create("pd_sprites.pvr.ccz");
	_actors->getTexture()->setAliasTexParameters();

	this->addChild(_actors);*/

	//this->initHero();

	/*auto visibleSize = Director::getInstance()->getVisibleSize();
		this->m_origin = Director::getInstance()->getVisibleOrigin();
		this->m_fScreenWidth = visibleSize.width;
		this->m_fScreenHeight = visibleSize.height;
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pd_sprites.plist");
		m_pSpriteNodes = SpriteBatchNode::create("pd_sprites.pvr.ccz");
		this->addChild(m_pSpriteNodes);
		m_pHero = Hero::create();
		m_pHero->setPosition( m_origin + Point(100, 100) );
		m_pHero->runIdleAction();
		m_pHero->setZOrder(m_fScreenHeight - m_pHero->getPositionY());
		m_pSpriteNodes->addChild(m_pHero);*/
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


/*void GameLayer::initHero()
{
	this->_hero=Hero::create();
	this->_actors->addChild(this->_hero);

	this->_hero->setPosition(ccp(this->_hero->_centerToSides,80));

	this->_hero->_desiredPosition=this->_hero->getPosition();

	this->_hero->idle();
}*/
/*bool GameLayer::init()
{
 bool ret = false;
 do {
  CC_BREAK_IF( !Layer::init());
  m_pTiledMap = TMXTiledMap::create("pd_tilemap.tmx");
  this->addChild(m_pTiledMap, -10);
  ret = true;
 } while(0);
 return ret;
}*/

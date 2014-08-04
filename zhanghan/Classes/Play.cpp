#include "Play.h"
#include "OperateLayer.h"
#include "HeroLayer.h"
USING_NS_CC;

Scene* Play::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Play::create();
	scene->addChild(layer);

	// add layer as a child to scene
	
	
	auto herolayer=HeroLayer::create();
	scene->addChild(herolayer);
	auto operateLayer = OperateLayer::create();
	scene->addChild(operateLayer);
	// return the scene
operateLayer->setHeroLayer(herolayer->getHeroLayer());
// CCLayerMultiplex* clayer = CCLayerMultiplex::create(herolayer, operateLayer, NULL);  
 //scene->addChild(clayer,1);
	return scene;
	
}

// on "init" you need to initialize your instance
bool Play::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Layer::init() )
	{
	
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//¼ÓÈëµØÍ¼
	m_pTiledMap = TMXTiledMap::create("map.tmx");
	    _background = m_pTiledMap->layerNamed("Background");
	//	_background->setAnchorPoint(ccp(0,0));
	this->addChild(m_pTiledMap);

	return true;
}


void Play::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

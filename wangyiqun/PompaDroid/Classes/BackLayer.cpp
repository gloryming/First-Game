#include "BackLayer.h"
USING_NS_CC;

BackLayer::BackLayer() :m_pTiledMap(NULL){

}

BackLayer::~BackLayer(){

}

bool BackLayer::init(){
	bool ret = false;
	do {
		CC_BREAK_IF(!Layer::init());
		m_pTiledMap = TMXTiledMap::create("tiles.tmx");
		this->addChild(m_pTiledMap, -5);
		ret = true;
	} while (0);
	return ret;
}
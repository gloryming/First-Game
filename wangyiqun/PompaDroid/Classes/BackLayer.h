#ifndef __BACK_LAYER_H__
#define __BACK_LAYER_H__

#include "cocos2d.h"

class BackLayer: public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	BackLayer();
	~BackLayer();
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
//	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(BackLayer);
	cocos2d::TMXTiledMap* m_pTiledMap;
};

#endif // __PLAY_SCENE_H__

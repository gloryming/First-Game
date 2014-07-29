#ifndef __POMPADROID_LAYER_H__
#define __POMPADROID_LAYER_H__

#include "cocos2d.h"

class PompaDroid : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menustartCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(PompaDroid);
};

#endif // __POMPADROID_LAYER_H__

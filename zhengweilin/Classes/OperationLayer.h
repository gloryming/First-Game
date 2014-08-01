#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class OperationLayer :public Layer
{
public:
	OperationLayer();
	~OperationLayer();

	virtual bool init();

	CREATE_FUNC(OperationLayer);
};


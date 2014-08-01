#include "MainScene.h"
#include "GameScene.h"

MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}

bool MainScene::init(){

	auto winSize = Director::getInstance()->getWinSize();

	bool ret = false;

	do{
		CC_BREAK_IF(!Scene::init());

		_mLayer = Layer::create();
		this->addChild(_mLayer, 0);

		ret = true;
	} while (0);
	
	auto background = Sprite::create("bg_title.png");
	background->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(background);

	auto title = Sprite::create("txt_title.png");
	title->setPosition(winSize.width / 2, winSize.height * 0.7f);
	this->addChild(title);

	auto title2 = Sprite::create("txt_touchtostart.png");
	title2->setPosition(winSize.width / 2, winSize.height * 0.4f);
	this->addChild(title2);

	this->setScaleX(570.0f / 480.0f);
	this->setScaleY(320.0f / 384.0f);

	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);
	
	listener->onTouchBegan = [](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode)){
			log("Sprite began... x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
			target->setScale(1.1f);
			target->setOpacity(200);

			return true;
		}
		return false;
	};

	listener->onTouchEnded = [=](Touch* touch, Event* event){
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		log("Sprite onTouchEnded ...");
		target->setOpacity(255);
		target->setScale(1);
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5f, GameScene::create()));
		
	};
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, title2);


	return ret;
}
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
		this->addChild(m_spriteNodes,0);

		m_hero = Hero::create();
		m_hero->setPosition(m_origin + Point(100, 100));
		m_hero->runIdleAction();//
		m_hero->setZOrder(m_screenHeight - m_hero->getPositionY());
		m_spriteNodes->addChild(m_hero);

		Size tileSize = m_TiledMap->getTileSize();
		m_tileWidth = tileSize.width;
		m_tileHeight = tileSize.height;

		m_hero->attack = CC_CALLBACK_0(BackLayer::onHeroAttack, this);
		m_hero->stop = CC_CALLBACK_0(BackLayer::onHeroStop, this);
		m_hero->walk = CC_CALLBACK_2(BackLayer::onHeroWalk, this);
		m_hero->jump = CC_CALLBACK_0(BackLayer::onHeroJump, this);

		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Robot.plist");
		m_spriteNodesR = SpriteBatchNode::create("Robot.png");
		this->addChild(m_spriteNodesR,-1);//
		
		m_robots.reserve(ROBOT_NUM);

		for (int i = 0; i < ROBOT_NUM ; ++i)
		{
			this->addRobot();
		}

		this->scheduleUpdate();

		ret = true;
	} while (0);
	return ret;
}

void BackLayer::onHeroWalk(Point direction, float distance)
{
	m_hero->setFlippedX(direction.x < 0 ? true : false);
	m_hero->runWalkAction();
	Point velocity = direction * (distance < 1024 ? 1 : 3);
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
void BackLayer::onHeroJump()
{
	m_hero->runJumpAction();
}
void BackLayer::update(float dt)
{
	this->updateHero(dt);
	this->updateRobots(dt);
}

void BackLayer::updateHero(float dt)
{
	if (m_hero->getCurActionStatus() == ACTION_WALK||m_hero->getCurActionStatus()==ACTION_JUMP)//
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
		m_hero->setZOrder(m_screenHeight - m_hero->getPositionY());//
	}
}

void BackLayer::addRobot()
{
	Size winSize = Director::getInstance()->getWinSize();
	Point location = Point::ZERO;
	Robot* robot = Robot::create();

	float halfRobotFrameHeight = (robot->getDisplayFrame()->getRect().size.height) / 2;
	float heroPosX = m_hero->getPositionX();
	float halfWinWidth = (winSize.width / 2);
	while (fabsf(heroPosX - location.x) < 150)
	{
		if (heroPosX < halfWinWidth)
		{
			location.x = m_hero->getPositionX() + CCRANDOM_0_1() * halfWinWidth*1.5;//
		}
		else if (heroPosX >(m_TiledMap->getMapSize().width * m_tileWidth - halfWinWidth)) {
			location.x = m_hero->getPositionX() - CCRANDOM_0_1() * halfWinWidth;
		}
		else {
			location.x = m_hero->getPositionX() + CCRANDOM_MINUS1_1() * halfWinWidth;
		}
	}
	float maxY = m_tileHeight +halfRobotFrameHeight;
	location.y = CCRANDOM_0_1() * maxY;
	if (location.y < halfRobotFrameHeight)
	{
		location.y = halfRobotFrameHeight;
	}
	robot->attack = CC_CALLBACK_0(BackLayer::onRobotAttack, this, robot);
	robot->setPosition(m_origin + location);
	robot->setZOrder(m_screenHeight - robot->getPositionY());
	robot->runIdleAction();
	robot->setAtk(5);
	robot->setHp(30);
	robot->setVelocity(Point(0.5f, 0.5f));
	robot->setCatchArea(200);//200
	robot->setAttackArea(25);
	m_robots.pushBack(robot);
	m_spriteNodesR->addChild(robot);
}

void BackLayer::updateRobots(float dt) {
	//Object *pObj = NULL;
	Point distance = Point::ZERO;

	Point heroLocation = m_hero->getPosition();
//	Array *pRemovedEnemies = Array::create();
	Vector<Robot*> _robots;
	for (auto robot:m_robots)
	{
		//Robot *robot = (Robot*)pObj;
		robot->execute(heroLocation, m_hero->getDisplayFrame()->getRect().size.width);
		if (robot->getCurActionStatus() == ACTION_WALK)
		{
			Point location = robot->getPosition();
			Point direction = robot->getMoveDirection();

			Point expect = location + direction;
			float halfEnemyFrameHeight = (robot->getDisplayFrame()->getRect().size.height) / 2;
			if (expect.y < halfEnemyFrameHeight || expect.y >(m_tileHeight * 3 + halfEnemyFrameHeight))
			{
				direction.y = 0;
			}
			robot->setFlippedX(direction.x < 0 ? true : false);
			robot->setPosition(location + direction);
			robot->setZOrder(m_screenHeight- robot->getPositionY());//
			log(robot->getPositionZ());
			//robot->setPositionZ(m_screenHeight - robot->getPositionY());
		}
	}
	for(auto robot:_robots)//
	{
		//Robot* robot = (Robot*)pObj;
		m_robots.erase(m_robots.find(robot));
		m_spriteNodesR->removeChild(robot, true);
	}
	_robots.clear();
}

void BackLayer::onRobotAttack(Character* sp)
{
}
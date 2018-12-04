/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "World.h"
#include "SimpleAudioEngine.h"
#include "../proj.win32/Block.h"
#include "../proj.win32/Crane.h"
#include "../proj.win32/GameOver.h"
#include "../proj.win32/Hud.h"
USING_NS_CC;

Scene* World::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = World::create();
	return layer;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool World::init()
{

    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
	mCameraScroll = false;
	getPhysicsWorld()->setGravity(getPhysicsWorld()->getGravity() * 8.f);
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 center = Vec2(visibleSize.width / 2 , visibleSize.height/2 + origin.y);
	mBackgroundSprite = Sprite::create("img/Background_2.png");
	mBackgroundSprite->setAnchorPoint(Vec2::ZERO);
	mBackgroundSprite->setPosition(0.f, 0.f);
	this->addChild(mBackgroundSprite, 0);
	
	Sprite* craneSprite = Sprite::create("img/Claw.png");
	craneSprite->setAnchorPoint(Vec2(0.5f, 1.f));
	Vec2 cranePosition = Vec2(center.x, visibleSize.height);
	Vec2 craneRelativeAttachPoint = Vec2(0.f, (craneSprite->getContentSize().height + 35.f) *-1);
	Crane* crane = Crane::CreateCrane(400.f, craneRelativeAttachPoint, cranePosition, craneSprite, this);
	mEntities.push_back(crane);
	crane->Init();

	mHud = Hud::CreateHud(cocos2d::Vec2::ZERO, this);
	cocos2d::Label* titleLabel = cocos2d::Label::createWithSystemFont("Omnidrone Test", "Arial", 15);
	titleLabel->setPosition(cocos2d::Vec2::ZERO);
	titleLabel->setAnchorPoint(cocos2d::Point(0, 1));
	titleLabel->enableShadow();
	mHud->CreateHudChild(titleLabel, cocos2d::Vec2(visibleSize.width - 130.f, -10.f));
	
	cocos2d::Sprite* sprite = Sprite::create("img/Block_1.png");
	Vec2 basePosition = Vec2(center.x, (center.y - 200.f) + sprite->getContentSize().height/2);
	auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0.1f, 0.1f, 0.7f));
	physicsBody->setDynamic(false);
	sprite->addComponent(physicsBody);	
	Block* baseBlock = Block::CreateBlock(100, basePosition, sprite, this);
	mTopBlock = baseBlock;
	mEntities.push_back(baseBlock);

	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = [=](cocos2d::EventKeyboard::KeyCode code, cocos2d::Event * event)->void {
		if (code == cocos2d::EventKeyboard::KeyCode::KEY_SPACE) 
		{
			Message* msg = new Message{ MESSAGE_TYPE::INPUT_SPACEBAR_PRESSED };
			this->BroadcastMessage(msg);
		}
		
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();
    return true;
}

void World::update(float delta)
{
	for (std::vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); it++)
	{
		(*it)->Update(delta);
	}
	mHud->Update(delta);
	//Add new entities created within this loop
	for (std::vector<Entity*>::iterator it = mNewEntities.begin(); it != mNewEntities.end(); it++)
	{
		mEntities.push_back((*it));
	}
	mNewEntities.clear();

	if (mCameraScroll) 
	{
		float previousCameraPosY, newCameraPosY;
		previousCameraPosY = _defaultCamera->getPositionY();
		newCameraPosY = previousCameraPosY + 150.f * delta;
		float cameraDelta = newCameraPosY - previousCameraPosY;
		_defaultCamera->setPositionY(newCameraPosY);
		mCamerScrollDistance -= cameraDelta;
		if (mCamerScrollDistance <= 0.f) 
			mCameraScroll = false;
	}
	
	if (CheckGameOverCondition()) 
	{
		this->DecrementScore();
		auto scene = GameOver::createScene(mScore);
		Director::getInstance()->replaceScene(scene);
	}
	/*USE SOME KIND OF NICE PARALLAX*/

}


Block* World::SpawnBlock(cocos2d::Vec2 &aPosition, unsigned int aPoints)
{
	cocos2d::Sprite* sprite = Sprite::create("img/Block_1.png");
	auto physicsBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(1.0f, 0.2f, 0.8f));
	sprite->addComponent(physicsBody);
	Block* newBlock = Block::CreateBlock(aPoints, aPosition, sprite, this);
	if (newBlock)
	{
		mCameraScroll = true;
		mCamerScrollDistance = 70.f;
		mNewEntities.push_back(newBlock);
		return newBlock;
	}
	else
		return nullptr;
}

void World::BroadcastMessage(Message* aMessage)
{
	for (std::vector<Entity*>::iterator it = mEntities.begin(); it != mEntities.end(); it++)
	{
		(*it)->ReceiveMessage(aMessage);
	}
	mHud->ReceiveMessage(aMessage);
}

const bool World::CheckGameOverCondition() 
{
	if (mTopBlock)
	{
		std::string position = "" + std::to_string(mTopBlock->GetPosition().y);
		if (mTopBlock->GetPosition().y <= _defaultCamera->getPositionY() - this->getContentSize().height / 2)
			return true;
		else
			return false;
	}
	return false;
}

void World::SetTopBlock(Block* aBlock) 
{
	if(aBlock)
		mTopBlock = aBlock;
}

void World::StopScrolling() 
{
	mCameraScroll = false;
}

void World::IncrementScore() 
{
	if (mTopBlock)
	{
		mScore += mTopBlock->GetPoints();
		MessageScore* msg = new MessageScore(MESSAGE_TYPE::CHANGE_SCORE, mScore);
		this->BroadcastMessage(msg);
	}
}

void World::DecrementScore()
{
	if (mTopBlock)
	{
		mScore -= mTopBlock->GetPoints();
		MessageScore* msg = new MessageScore(MESSAGE_TYPE::CHANGE_SCORE, mScore);
		this->BroadcastMessage(msg);
	}
}

World::~World() 
{
	//Scene destructors are managed by smart pointers inside cocos2dx engine
}
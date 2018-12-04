#include "Crane.h"
#include "World.h"
#include "Block.h"

Crane* Crane::CreateCrane(float aVelocity, cocos2d::Vec2 aAttachPoint, cocos2d::Vec2 aPosition, cocos2d::Sprite* aSprite, cocos2d::Node* aParent)
{
	if ((aSprite) && (aParent))
	{
		Crane* newCrane = new Crane(aVelocity, aAttachPoint, aPosition, aSprite, aParent);
		aParent->addChild(newCrane->GetSprite());
		return newCrane;
	}
	else
		return nullptr;
}

Crane::Crane(float aVelocity, cocos2d::Vec2 aAttachPoint, cocos2d::Vec2 aPosition, cocos2d::Sprite* aSprite, cocos2d::Node* aParent)
	: Entity(aPosition, aSprite, aParent)
{
	this->mVelocity = aVelocity;
	this->mRelativeAttachPoint = aAttachPoint;
	this->mWorldAttachPoint = cocos2d::Vec2(this->GetPosition().x + mRelativeAttachPoint.x, this->GetPosition().y + mRelativeAttachPoint.y);
	this->mCooldown = -1.f;
}

Crane::~Crane()
{
}

void Crane::Update(float delta)
{
	mCooldown -= delta;
	cocos2d::Vec2 newPosition = this->GetPosition();
	newPosition.x += mVelocity * delta;
	if ((newPosition.x <= (this->GetParentNode()->getBoundingBox().getMinX() - (this->GetSprite()->getBoundingBox().size.width / 2))) 
		|| (newPosition.x >= (this->GetParentNode()->getBoundingBox().getMaxX() + (this->GetSprite()->getBoundingBox().size.width / 2))))
		mVelocity *= -1;
	
	World* world = dynamic_cast<World*>(this->GetParentNode());
	if (world)
		newPosition.y = world->getDefaultCamera()->getPositionY() + world->getContentSize().height/2;

	this->SetPosition(newPosition);

	this->mWorldAttachPoint = cocos2d::Vec2(this->GetPosition().x + mRelativeAttachPoint.x, this->GetPosition().y + mRelativeAttachPoint.y);
	if (mAttachedBlock)
		mAttachedBlock->SetPosition(this->mWorldAttachPoint);
	else 
	{
		if (mCooldown <= 0.f)
			RequestBlock();
	}
}

void Crane::Init() 
{
	RequestBlock();
}

void Crane::RequestBlock() 
{
	World* world = dynamic_cast<World*>(this->GetParentNode());
	if (world)
	{	
		mAttachedBlock = world->SpawnBlock(this->mWorldAttachPoint, 100);
		if (mAttachedBlock)
		{
			mAttachedBlock->GetSprite()->getPhysicsBody()->setEnabled(false);
			world->IncrementScore();
		}
	}
}

void Crane::ReceiveMessage(Message* aMessage)
{
	switch (aMessage->type)
	{
	case INPUT_SPACEBAR_PRESSED:
		if (mAttachedBlock)
		{
			mAttachedBlock->GetSprite()->getPhysicsBody()->setEnabled(true);
			World* world = dynamic_cast<World*>(this->GetParentNode());
			if (world)
				world->SetTopBlock(mAttachedBlock);
			mAttachedBlock = nullptr;
			mCooldown = 1.f;
		}
		break;
	case GAME_OVER:
		break;
	case CHANGE_SCORE:
		break;
	default:
		break;
	}
}
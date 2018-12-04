#include "Entity.h"

Entity::Entity(cocos2d::Vec2 aPosition, cocos2d::Sprite* aSprite, cocos2d::Node* aParent)
	: mPosition(aPosition), mSprite(aSprite), mParent(aParent) 
{
	this->SetPosition(aPosition);
}

Entity::~Entity() 
{
	mSprite->release();
}

void Entity::SetSprite(cocos2d::Sprite* aSprite)
{
	if (aSprite)
		mSprite = aSprite;
}

cocos2d::Sprite* Entity::GetSprite() const
{
	return mSprite;
}

void Entity::SetPosition(cocos2d::Vec2 aPosition)
{
	mPosition = aPosition;
	if (mSprite)
		mSprite->setPosition(aPosition);
}

const cocos2d::Vec2 Entity::GetPosition() const
{
	mPosition = mSprite->getPosition();
	return mPosition;
}

void Entity::SetParentNode(cocos2d::Node* aParent)
{
	mParent = aParent;
}

cocos2d::Node* Entity::GetParentNode() const 
{
	return mParent;
}
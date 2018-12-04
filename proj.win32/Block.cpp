#include "Block.h"
#include "World.h"

Block* Block::CreateBlock(unsigned int aPoints, cocos2d::Vec2 aPosition, cocos2d::Sprite* aSprite, cocos2d::Node* aParent)
{
	if ((aSprite) && (aParent))
	{
		Block* newBlock = new Block(aPoints, aPosition, aSprite, aParent);
		aParent->addChild(newBlock->GetSprite());
		return newBlock;
	}
	else
		return nullptr;
}

Block::Block(unsigned int aPoints, cocos2d::Vec2 aPosition, cocos2d::Sprite* aSprite, cocos2d::Node* aParent)
	: Entity(aPosition, aSprite, aParent)
{
	this->mPoints = aPoints;
}

Block::~Block() 
{
}

void Block::Update(float delta) 
{

}

void Block::Init()
{

}

void Block::ReceiveMessage(Message* aMessage)
{
	switch (aMessage->type)
	{
	case INPUT_SPACEBAR_PRESSED:
		break;
	case GAME_OVER:
		break;
	case CHANGE_SCORE:
		break;
	default:
		break;
	}
}

const unsigned int Block::GetPoints()const
{
	return mPoints;
}
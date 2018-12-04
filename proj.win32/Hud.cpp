#include "Hud.h"
#include "World.h"
#include "Message.h"

Hud* Hud::CreateHud(cocos2d::Vec2 aPosition, cocos2d::Node* aParent)
{
	if (aParent)
	{
		Hud* newHud = new Hud(aPosition, aParent);
		return newHud;
	}
	else
		return nullptr;
}

Hud::Hud(cocos2d::Vec2 aPosition, cocos2d::Node* aParent)
	: mPosition(aPosition), mParent(aParent)
{
	this->SetPosition(aPosition);
	mScoreLabel = cocos2d::Label::createWithSystemFont("000", "Arial", 25);
	mScoreLabel->setAnchorPoint(cocos2d::Point(0, 1));
	mScoreLabel->setTextColor(cocos2d::Color4B::ORANGE);
	mScoreLabel->enableShadow();
	this->CreateHudChild(mScoreLabel, cocos2d::Vec2(110.f, -10.f));
	cocos2d::Label* scoreTitle = cocos2d::Label::createWithSystemFont("SCORE:", "Arial", 25);
	scoreTitle->setAnchorPoint(cocos2d::Point(0, 1));
	scoreTitle->setTextColor(cocos2d::Color4B::RED);
	scoreTitle->enableShadow();
	this->CreateHudChild(scoreTitle, cocos2d::Vec2(10.f, -10.f));
}

Hud::~Hud()
{
	mScoreLabel->release();
	for (std::vector<Child*>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
	{
		(*it)->mChildNode->release();
	}
}

void Hud::SetPosition(cocos2d::Vec2 aPosition)
{
	mPosition = aPosition;
	for (std::vector<Child*>::iterator it = mChildren.begin(); it != mChildren.end(); it++)
	{
		cocos2d::Vec2 newPosition = this->GetPosition();
		newPosition.x += (*it)->mRelativePosition.x;
		newPosition.y += (*it)->mRelativePosition.y;
		if ((*it)->mChildNode)
		{
			(*it)->mChildNode->setPosition(newPosition);
		}
	}
}

const cocos2d::Vec2 Hud::GetPosition() const
{
	return mPosition;
}

void Hud::SetParentNode(cocos2d::Node* aParent)
{
	mParent = aParent;
}

cocos2d::Node* Hud::GetParentNode() const
{
	return mParent;
}

void Hud::Update(float delta)
{
	cocos2d::Vec2 newPosition = this->GetPosition();
	World* world = dynamic_cast<World*>(this->GetParentNode());
	if (world)
		newPosition.y = world->getDefaultCamera()->getPositionY() + world->getContentSize().height / 2;
	this->SetPosition(newPosition);
}

void Hud::Init()
{

}

void Hud::ReceiveMessage(Message* aMessage)
{
	switch (aMessage->type)
	{
	case INPUT_SPACEBAR_PRESSED:
		break;
	case GAME_OVER:
		break;
	case CHANGE_SCORE:
		MessageScore* ms = reinterpret_cast<MessageScore*>(aMessage); //I WANT TO USE DYNAMIC_CAST But cocos2d type_defs wont allow me???
		mScoreLabel->setString(std::to_string(ms->score));
		break;
	}
}

void Hud::PushChild(Child* aChild) 
{
	mChildren.push_back(aChild);
}

void Hud::CreateHudChild(cocos2d::Node* aNode, cocos2d::Vec2 aRelativePosition) 
{
	if (aNode) 
	{
		this->GetParentNode()->addChild(aNode);
		Child* newChild = new Child(aNode, aRelativePosition);
		mChildren.push_back(newChild);
	}
}
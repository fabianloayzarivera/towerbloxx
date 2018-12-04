#pragma once

#include "Entity.h"

class Message;
class Block : public Entity
{
private:
	unsigned int	mPoints;

public:
	static Block* CreateBlock(unsigned int aPoints, cocos2d::Vec2 aPosition, cocos2d::Sprite* aSprite = nullptr, cocos2d::Node* aParent = nullptr);
	Block(unsigned int aPoints, cocos2d::Vec2 aPosition, cocos2d::Sprite* aSprite = nullptr, cocos2d::Node* aParent = nullptr);
	~Block();
	virtual void				Update(float delta) override;
	virtual void				Init() override;
	virtual void				ReceiveMessage(Message* aMessage) override;
	const unsigned int			GetPoints() const ;
};
#pragma once
#include "cocos2d.h"

class Message;
class Entity
{
private:
	cocos2d::Sprite*			mSprite;
	mutable cocos2d::Vec2		mPosition;
	cocos2d::Node*				mParent;
public:
	Entity(cocos2d::Vec2 aPosition, cocos2d::Sprite* aSprite = nullptr, cocos2d::Node* aParent = nullptr);
	virtual						~Entity();
	void						SetSprite(cocos2d::Sprite* aSprite = nullptr);
	cocos2d::Sprite*			GetSprite() const;
	void						SetPosition(cocos2d::Vec2 aPosition);
	const	cocos2d::Vec2		GetPosition() const;
	void						SetParentNode(cocos2d::Node* aParent = nullptr);
	cocos2d::Node*				GetParentNode() const;
	virtual void				Update(float delta) = 0;
	virtual void				Init() = 0;
	virtual void				ReceiveMessage(Message* aMessage) = 0;
};
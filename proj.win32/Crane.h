#pragma once
#include "Entity.h"

class Block;
class Message;
class Crane : public Entity 
{
private:
	float			mVelocity;
	cocos2d::Vec2	mRelativeAttachPoint;
	cocos2d::Vec2	mWorldAttachPoint;
	Block*			mAttachedBlock;
	float			mCooldown;
public:
	static Crane* CreateCrane(float aVelocity, cocos2d::Vec2 aAttachPoint,cocos2d::Vec2 aPosition, cocos2d::Sprite* aSprite = nullptr, cocos2d::Node* aParent = nullptr);
	Crane(float aVelocity, cocos2d::Vec2 aAttachPoint, cocos2d::Vec2 aPosition, cocos2d::Sprite* aSprite = nullptr, cocos2d::Node* aParent = nullptr);
	~Crane();
	void						RequestBlock();
	virtual void				Update(float delta) override;
	virtual void				Init() override;
	virtual void				ReceiveMessage(Message* aMessage) override;
};
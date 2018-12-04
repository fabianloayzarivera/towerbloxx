#pragma once
#include "cocos2d.h"
#include <vector>

class Message;
struct Child 
{
	Child(cocos2d::Node* aChildNode, cocos2d::Vec2 aRelativePosition) { mChildNode = aChildNode; mRelativePosition = aRelativePosition; }
	cocos2d::Node* mChildNode;
	cocos2d::Vec2 mRelativePosition;
};

class Hud
{
private:
	cocos2d::Label*				mScoreLabel;
	mutable cocos2d::Vec2		mPosition;
	cocos2d::Node*				mParent;
	std::vector<Child*>			mChildren;
public:
	static Hud* CreateHud(cocos2d::Vec2 aPosition, cocos2d::Node* aParent = nullptr);
	Hud(cocos2d::Vec2 aPosition, cocos2d::Node* aParent = nullptr);
	~Hud();
	void						SetPosition(cocos2d::Vec2 aPosition);
	const	cocos2d::Vec2		GetPosition() const;
	void						SetParentNode(cocos2d::Node* aParent = nullptr);
	cocos2d::Node*				GetParentNode() const;
	void						PushChild(Child* aChild);
	void						CreateHudChild(cocos2d::Node* aNode, cocos2d::Vec2 aRelativePosition);
	void						Update(float delta);
	void						Init();
	void						ReceiveMessage(Message* aMessage);
	
};
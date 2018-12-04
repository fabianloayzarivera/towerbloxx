
#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"
#include <vector>;

class GameOver : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene(const int &aScore);

	virtual bool init();

	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(GameOver);


private:
	void GoToGameScene(cocos2d::Ref *sender);
	void GoToMainMenuScene(cocos2d::Ref *sender);
	~GameOver() {}
};

#endif // __GAME_OVER_H__
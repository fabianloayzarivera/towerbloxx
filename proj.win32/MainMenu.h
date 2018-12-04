
#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "cocos2d.h"
#include <vector>;

class MainMenu : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainMenu);


private:
	void GoToGameScene(cocos2d::Ref *sender);
	~MainMenu() {}
};

#endif // __MAIN_MENU_H__
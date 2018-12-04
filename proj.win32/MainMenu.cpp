#include "MainMenu.h"
#include "World.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* MainMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenu::create();
	scene->addChild(layer);

	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' \n");
}

bool MainMenu::init()
{

	if (!Scene::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Vec2 center = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	auto backgroundSprite = Sprite::create("img/Background_1.png");
	if (!backgroundSprite)
		return false;
	backgroundSprite->setPosition(center);
	this->addChild(backgroundSprite,0);

	auto titleSprite = Sprite::create("img/Title_1.png");
	if (!titleSprite)
		return false;
	titleSprite->setPosition(Vec2(center.x, center.y + 200.f));
	this->addChild(titleSprite);

	auto playButton = MenuItemImage::create("img/Button_play.png", "Button_play_clicked.png", CC_CALLBACK_1(MainMenu::GoToGameScene, this));
	playButton->setPosition(center);

	auto menu = Menu::create(playButton, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);
	return true;
}

void MainMenu::GoToGameScene(cocos2d::Ref *sender) 
{
	auto scene = World::createScene();
	Director::getInstance()->replaceScene(scene);
}

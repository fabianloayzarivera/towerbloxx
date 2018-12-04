#include "GameOver.h"
#include "MainMenu.h"
#include "World.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

int tempScore;
Scene* GameOver::createScene(const int &aScore)
{
	tempScore = aScore;
	auto scene = Scene::create();
	auto layer = GameOver::create();
	scene->addChild(layer);
	
	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' \n");
}

bool GameOver::init()
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
	this->addChild(backgroundSprite, 0);

	cocos2d::Label* titleLabel = cocos2d::Label::createWithSystemFont("Final Score:", "Arial", 40);
	titleLabel->setPosition(cocos2d::Vec2(center.x, center.y + 150.f));
	titleLabel->setAnchorPoint(cocos2d::Point(0.5f, 0.5f));
	titleLabel->setTextColor(cocos2d::Color4B::RED);
	titleLabel->enableShadow();
	this->addChild(titleLabel);

	cocos2d::Label* scoreLabel = cocos2d::Label::createWithSystemFont(std::to_string(tempScore), "Arial", 50);
	scoreLabel->setPosition(cocos2d::Vec2(center.x, center.y + 110.f));
	scoreLabel->setAnchorPoint(cocos2d::Point(0.5f, 0.5f));
	scoreLabel->enableShadow();
	this->addChild(scoreLabel);

	auto retryButton = MenuItemImage::create("img/Button_retry.png", "Button_retry_clicked.png", CC_CALLBACK_1(GameOver::GoToGameScene, this));
	retryButton->setPosition(center);

	auto mainMenuButton = MenuItemImage::create("img/Button_main_menu.png", "img/Button_main_menu_clicked.png", CC_CALLBACK_1(GameOver::GoToMainMenuScene, this));
	mainMenuButton->setPosition(Vec2(center.x, center.y - 150.f));

	auto menu = Menu::create(retryButton, mainMenuButton, NULL);
	menu->setPosition(Point::ZERO);

	this->addChild(menu);

	UserDefault *def = UserDefault::getInstance();
	auto highScore = def->getIntegerForKey("HIGHSCORE", 0);

	if (tempScore > highScore)
	{
		highScore = tempScore;
		def->setIntegerForKey("HIGHSCORE", tempScore);
	}
	def->flush();

	std::string strHigh = "HIGHSCORE: " + std::to_string(highScore);
	cocos2d::Label* highScoreLabel = cocos2d::Label::createWithSystemFont(strHigh, "Arial", 50);
	highScoreLabel->setPosition(cocos2d::Vec2(center.x, center.y + 200.f));
	highScoreLabel->setAnchorPoint(cocos2d::Point(0.5f, 0.5f));
	highScoreLabel->setTextColor(cocos2d::Color4B::YELLOW);
	highScoreLabel->enableShadow();
	this->addChild(highScoreLabel);

	return true;
}

void GameOver::GoToGameScene(cocos2d::Ref *sender)
{
	auto scene = World::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameOver::GoToMainMenuScene(cocos2d::Ref *sender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}

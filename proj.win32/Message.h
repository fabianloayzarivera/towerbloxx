#pragma once
enum MESSAGE_TYPE { INPUT_SPACEBAR_PRESSED, GAME_OVER, CHANGE_SCORE };

struct Message 
{
	MESSAGE_TYPE type;
};

struct MessageScore : public Message 
{
	MessageScore(MESSAGE_TYPE mt, int aScore) { type = mt; score = aScore; }
	int score;
};


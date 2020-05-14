#pragma once
#include <string>
#include <SDL.h>
#include <vector>

using namespace std;

struct LBent
{
	string name;
	Uint64 score;

	LBent() {};
	LBent(Uint64 s, const std::string& n) : score(s), name(n) {}

	bool operator>(const LBent& str) const
	{
		return(score > str.score);
	}
};


class Menu
{
public:
	int menuStage;
	//NewGame *newgame;
	SDL_Texture *Tbackground, *TngButton, *TlgButton, *ThsButton,  *THL, *TBack;

	SDL_Rect background, ngButton, lgButton, hsButton, difButton, startPosButton, HL, Back;

	SDL_Rect ngButtonsrc, lgButtonsrc, hsButtonsrc, HLsrc;
	int selectedButton;

	//int lastUpdate;

	Menu();

	
	void Loop(int& Difficulty, int& startPos, int& GameRunning,bool &ng, string& name);
	void Render(int Difficulty, int startPos, string &name);

};

class NewGame
{
public:
	//int difficulty;
	//string name;

	 Sint32 cursor;
	 Sint32 selection_len;
	 char* composition;

	int selectedButton;

	SDL_Texture* Tbackground, * TnameSlot, * TdifButton[4], *TstartPos[5], * TstartPosButton[5], *THL, *TngButton, *Tback;

	SDL_Rect nameSlots, difficultyRs, startPosRs, HLs, ngButtons, backs;
	SDL_Rect background, nameSlot, difficultyR, startPosR, HL, ngButton, back;

	bool nmslt;

	NewGame();

	void Render(int Difficulty, int startPos, string& name);
	void Loop(int& Difficulty, int& startPos, int& GameRunning, int&menuStage, string& name);

};


class GameOver
{
public:
	SDL_Rect bg;
	SDL_Texture *Tbgw, *Tbgl;

	int wl;

	vector<LBent> players;

	

	GameOver();
	int Loop(Uint64 Score, bool wl, string& name);
	void render(Uint64 Score);

	void addToLb(Uint64 Score, string& name);
};


class LeaderboardScreen
{
public:
	SDL_Rect bg;
	SDL_Texture* tbg;
	vector<LBent> scores;

	bool read = 0;

	LeaderboardScreen();
	void loop(int& menuStage);
	void render();
};


class Button
{

};
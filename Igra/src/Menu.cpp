#include "Menu.h"
#include "Game.h"
#include "TextureManager.h"
#include <fstream>
//#include <bits/stdc++.h> 
#include <algorithm>
#include <iostream>
//#include <streambuf>


NewGame *newgame;

Menu::Menu()
{
	Tbackground = TextureManager::LoadTexture("assets/MainMenu.png");
	TngButton = TextureManager::LoadTexture("assets/StartGame.png");
	TlgButton = TextureManager::LoadTexture("assets/Load last session.png");
	ThsButton = TextureManager::LoadTexture("assets/hiscore.png");
	THL = TextureManager::LoadTexture("assets/MenuHLight.png");

	//---------------//
	//Start game menu//
	//---------------//

	newgame = new NewGame;

	//vem da mam prevect recov, to sm opazu sele po tem ka sm koncou, prej rectov nism sploh razumel, pa razumem da so source recti pozicija na .png


	background.x = background.y = 0;
	background.w = 1920;
	background.h = 1080;


	ngButtonsrc.x = ngButtonsrc.y = 0;
	ngButton.x = 510;
	ngButton.y = 400;
	ngButton.w = ngButtonsrc.w = 800;
	ngButton.h = ngButtonsrc.h = 200;

	lgButton.x = 510;
	lgButton.y = 620;
	lgButtonsrc.x = lgButtonsrc.y = 0;
	lgButton.w = lgButtonsrc.w =800;
	lgButton.h = lgButtonsrc.h =200;

	hsButtonsrc.x = hsButtonsrc.y = 0;
	hsButton.x = 510;
	hsButton.y = 840;
	hsButton.w =hsButtonsrc.w= 800;
	hsButton.h = hsButtonsrc.h =200;

	HL.x = 510;
	HL.y = 400;
	HLsrc.x = HLsrc.y = 0;
	HL.w = HLsrc.w=800;
	HL.h = HLsrc.h=200;

	menuStage = 0;
}

void Menu::Loop(int& Difficulty, int& startPos, int &GameRunning, bool &ng)
{
	static bool pressed = 0;
	if(menuStage == 0)
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				selectedButton--;
				break;
			case SDLK_s:
				selectedButton++;
				break;
			case SDLK_SPACE:
				pressed = true;
				break;
			case SDLK_r:
				GameRunning = 3;
				break;

			}
			
		}
	if (selectedButton > 2)
		selectedButton = 0;
	else if (selectedButton < 0)
		selectedButton = 2;


	if (selectedButton == 0)
	{
		HL = ngButton;
		if (pressed)
			menuStage = 1;
	}
	else if (selectedButton == 1)
	{
		HL = lgButton;
		if (pressed)
		{
			ng = 0;
			GameRunning = true;
		}
	}
	else if (selectedButton == 2)
	{
		HL = hsButton;
		if (pressed)
			menuStage = 2;
	}
		


	if (menuStage == 1)
	{
		newgame->Loop(Difficulty, startPos, GameRunning, menuStage);
	}
	if (menuStage == 2)
	{
		string tmp;
		cout << "LeaderBoard:\n";
		ifstream f("LeaderBoard.txt");
		while (getline(f,tmp))
			cout<<tmp <<"\n";
		menuStage = 0;
	}
	pressed = false;
}

NewGame::NewGame()
{

	Tbackground = TextureManager::LoadTexture("assets/Background.png");
	Tback = TextureManager::LoadTexture("assets/Back.png");

	THL = TextureManager::LoadTexture("assets/MenuHLight.png");

	TnameSlot = TextureManager::LoadTexture("assets/Blank_Button.png");

	//difficulty
	TdifButton[0] = TextureManager::LoadTexture("assets/easy.png");
	TdifButton[1] = TextureManager::LoadTexture("assets/normal.png");
	TdifButton[2] = TextureManager::LoadTexture("assets/hard.png");
	TdifButton[3] = TextureManager::LoadTexture("assets/impossible.png");

	//Start position
	TstartPosButton[0] = TextureManager::LoadTexture("assets/RR.png");
	TstartPosButton[1] = TextureManager::LoadTexture("assets/TL.png");
	TstartPosButton[2] = TextureManager::LoadTexture("assets/TR.png");
	TstartPosButton[3] = TextureManager::LoadTexture("assets/BR.png");
	TstartPosButton[4] = TextureManager::LoadTexture("assets/BL.png");

	TngButton = TextureManager::LoadTexture("assets/StartGame.png");

	backs.x = backs.y = 0;
	backs.w = back.w = 800;
	backs.h = back.h = 200;
	back.x = 50;
	back.y = 50;

	background.x = background.y = 0;
	background.w = 1920;
	background.h = 1080;

	ngButtons.x = ngButtons.y = 0;
	ngButton.x = 135 + 850;
	ngButton.y = 800;
	ngButton.w = ngButtons.w = 800;
	ngButton.h = ngButtons.h = 200;

	difficultyRs.x = difficultyRs.y = 0;
	difficultyR.x = 135 + 850;
	difficultyR.y = 550;
	difficultyR.w = difficultyRs.w = 800;
	difficultyR.h = difficultyRs.h = 200;

	startPosRs.x = startPosRs.y = 0;
	startPosR.x = 135;
	startPosR.y = 800;
	startPosR.w = startPosRs.w = 800;
	startPosR.h = startPosRs.h = 200;

	nameSlot.x = nameSlots.y = 0;
	nameSlot.x = 135;
	nameSlot.y = 550;
	nameSlot.w = nameSlots.w = 800;
	nameSlot.h = nameSlots.h = 200;

	HLs.x = HL.y = 0;
	HLs.w = 800;
	HLs.h = 200;

	HL = ngButton;

	selectedButton = 3;

	//cout << "Vpisi ime: ";
	//f getline(cin, name);

}

void NewGame::Loop(int& Difficulty, int& startPos, int& GameRunning, int& menuStage)
{
	static bool pressed = false;
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_w:
			if(selectedButton ==1)
				selectedButton =3;
			else if (selectedButton == 3)
				selectedButton = 1;
			else if (selectedButton == 2)
				selectedButton = 4;
			else if (selectedButton == 4)
				selectedButton = 2;
			break;
		case SDLK_s:
			if (selectedButton == 1)
				selectedButton = 3;
			else if (selectedButton == 3)
				selectedButton = 1;
			else if (selectedButton == 2)
				selectedButton = 4;
			else if (selectedButton == 4)
				selectedButton = 2;
			break;
		case SDLK_a:
			if(selectedButton == 1)
				selectedButton = 0;
			else if (selectedButton == 2)
				selectedButton = 1;
			else if (selectedButton == 0)
				selectedButton = 2;
			else if (selectedButton == 3)
				selectedButton = 4;
			else if (selectedButton == 4)
				selectedButton = 3;
			break;
		case SDLK_d:
			if(selectedButton ==0)
				selectedButton=1;
			else if (selectedButton == 2)
				selectedButton = 0;
			else if (selectedButton == 1)
				selectedButton = 2;
			else if (selectedButton == 3)
				selectedButton = 4;
			else if (selectedButton == 4)
				selectedButton = 3;
			break;
		case SDLK_SPACE:
			pressed = true;
			break;
		}

		
	}
	if (selectedButton == 0)
	{
		HL = back;
		if (pressed)
			menuStage = 0;
	}
	else if (selectedButton == 1)
	{
		HL = nameSlot;
	}
	else if (selectedButton == 2)
	{
		HL = difficultyR;
		if (pressed)
		{
			Difficulty++;
			if (Difficulty > 3)
				Difficulty = 0;
		}
	}
	else if (selectedButton == 3)
	{
		HL = startPosR;
		if (pressed)
		{
			startPos++;
			if (startPos > 4)
				startPos = 0;
		}
	}

	else if (selectedButton == 4)
	{
		HL = ngButton;
		if (pressed)
		{
			GameRunning = true;
		}
	}
	
	pressed = false;
}

void NewGame::Render(int Difficulty, int startPos)
{
	TextureManager::Draw(Tbackground, background, background);
	TextureManager::Draw(TngButton, ngButtons, ngButton);
	TextureManager::Draw(Tback, backs, back);
	TextureManager::Draw(TnameSlot, nameSlots, nameSlot);
	TextureManager::Draw(TdifButton[Difficulty], difficultyRs, difficultyR);
	TextureManager::Draw(TstartPosButton[startPos], startPosRs, startPosR);
	TextureManager::Draw(THL, HLs, HL);

}

void Menu::Render(int Difficulty, int startPos)
{
	if (!menuStage)
	{
		TextureManager::Draw(Tbackground, background, background);
		TextureManager::Draw(TngButton, ngButtonsrc, ngButton);
		TextureManager::Draw(TlgButton, lgButtonsrc, lgButton);
		TextureManager::Draw(ThsButton, hsButtonsrc, hsButton);
		TextureManager::Draw(THL, HLsrc, HL);
	}
	if (menuStage == 1)
		newgame->Render(Difficulty, startPos);
}

GameOver::GameOver()
{
	bg.x = bg.y = 0;
	bg.w = 1920;
	bg.h = 1080;

	Tbgw = TextureManager::LoadTexture("assets/GameOver_Won.png");
	Tbgl = TextureManager::LoadTexture("assets/GameOver_Lost.png");
	
}

int GameOver::Loop(Uint64 Score, bool wl)
{
	//cout << "looping\n";
	string temp;
	this->wl = wl;
		if (Game::event.type == SDL_KEYDOWN)
		{
			//cout << "Checking key\n";
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
			case SDLK_SPACE:
			case SDLK_RETURN:
			//	cout << "Pressed Key!\n";
				addToLb(Score, newgame->name);
				return 1;
				break;
			}
		}
	return 0;
}

void GameOver::render()
{
	if (wl)
		TextureManager::Draw(Tbgw, bg, bg);
		
	else
		TextureManager::Draw(Tbgl, bg, bg);

}


void GameOver::addToLb(Uint64 Score, string name)
{ 
	string tmp;
	
	LBent tp;

	ifstream idat("LeaderBoard.txt");

	LBent temp;
	temp.score = Score;
	temp.name = "name";

	int cnt = 0;

	bool isHs = false;
	if(idat.is_open())
	{
		while (idat.good() && cnt<5)
		{
			getline(idat, tp.name, ':');
			getline(idat, tmp, '\n');
			tp.score = atoi(tmp.c_str());
			players.push_back(tp);
			cnt++;
		}
		idat.close();

		for (auto& i : players)
		{
			if (Score > i.score || players.size() == 0)
				isHs = true;
		}
		if (isHs)
		{
			players.push_back(temp);
		}
			std::sort(players.begin(), players.end(), greater<LBent>());
			
			if(players.size()>5)
				players.erase(players.end()-1);
	}
	ofstream odat("LeaderBoard.txt");
	if (odat.is_open())
	{
		cout << "Leaderboard:\n";
		for (auto& i : players)
		{
			odat << i.name << ':' << to_string(i.score)<<'\n';
			cout << i.name << ':' << to_string(i.score)<<'\n';
		}
		odat.close();
	}
}

#pragma once
#include <fstream>
#include <list>
#include <vector>
#include "DataStruct.h"

using namespace std;

class Obj;
class StaticObject;


class LobbyScene2;
class InGameScene;
class ImageManager;

class SceneManager
{
private:
	HWND hWnd;
	HDC hdc;
	HDC memDC;
	HDC memDCBack;

	LobbyScene2* lobbyScene;
	InGameScene* inGameScene;


private:

	//없애야할 3인방
	vector<Obj*> inGameSceneDataVector;	//INGAME Scene Data
	vector<Obj*> CharacterDataVector;	//CHARACTER Data
	vector<Obj*> mapObjectVector;	//CHARACTER Data

public:
	SceneManager(HWND hWnd);
	~SceneManager();
	void Process(const int& stage);

	void LoadLobbyImageData();
public:
	void Input();
	void Update();
	void Render(HDC hdc, HDC backdc, HDC mdc);

	void LoadInGameImageData(const vector<pImageData>& bitmapVector);
	void LoadRedCharacterImageData(pImageData characterImage);
	void LoadBlueCharacterImageData(pImageData characterImage);
	void LoadRedCharacterStatsData(CharacterStatsData characterStats);
	void LoadBlueCharacterStatsData(CharacterStatsData characterStats);
	//추가
	void LoadStaticObjectData(const MapData& mapData);

};
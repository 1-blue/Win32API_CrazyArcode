#pragma once
#include <fstream>
#include "DataStruct.h"

class LobbyScene;
class InGameScene;
class ImageManager;
class SceneManager
{
private:
	HWND hWnd;
	HDC hdc;
	HDC memDC;
	HDC memDCBack;
	HBITMAP oldHBitMap{ NULL };

	LobbyScene* lobbyScene;
	InGameScene* inGameScene;

	SelectData selectData{ 0 ,0, 0 , false};		//요거에 선택한 캐릭터들, 맵번호, 게임시작여부 넣음

public:
	SceneManager(HWND hWnd);
	~SceneManager();
	void Process(const int& stage);

	void LoadLobbyData(const vector<pImageData>& lobbyData);

	const SelectData& GetSelectData();
	void LoadInGameBackGroundImage(const vector<pImageData>& inGameBackGround);
	void LoadCharacterData(const pImageData* characterImage, const CharacterStatsData* characterStats);
	void LoadMapData(const MapData& mapData);
	void LoadWaterBallonData(const pImageData waterBallon);

};
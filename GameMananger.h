#pragma once
#include "DataStruct.h"

class ImageManager;
class MapManager;
class SceneManager;
class LobbyScene;

class GameMananger
{
private:
	const int WND_WIDTH = 800;
	const int WND_HEIGHT = 600;

	//밑에 dc, hwnd 이런거 sceneManager로 옮기자
	HWND hWnd;
	HDC hdc;
	HDC memDC;
	HDC memDCBack;
	HBITMAP oldHBitMap{ NULL };
	SceneManager* sceneManager{ NULL };
	ImageManager* imageManager{ NULL };
	MapManager* mapManager{ NULL };
	int stage;
	bool isFirst{ true };
	SelectData selectData{ 0 ,0, 0 };		//요거에 선택한 캐릭터들, 맵번호 넣음
	vector<LobbyScene*> lobbyScene;

public:
	GameMananger(HWND hWnd);
	~GameMananger();

	void Run();

	void Input();
	void Update();
	void Render();

public:
	void LoadImageData();
	void LoadLobbyData(const vector<pImageData>& lobbyDataVector);
	void LoadMapData();

};


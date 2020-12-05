#pragma once
#include "DataStruct.h"

class ImageManager;
class MapManager;
class ObjectManager;
class LobbyScene;
class SceneMananger
{
private:
	const int WND_WIDTH = 800;
	const int WND_HEIGHT = 600;

	HWND hWnd;
	HDC hdc;
	HDC memDC;
	HDC memDCBack;
	HBITMAP oldHBitMap{ NULL };
	ObjectManager* objectManager{ NULL };
	ImageManager* imageManager{ NULL };
	MapManager* mapManager{ NULL };
	int stage;
	bool isFirst{ true };
	SelectData selectData{ 0 ,0, 0 };		//요거에 선택한 캐릭터들, 맵번호 넣음
	vector<LobbyScene*> lobbyScene;

public:
	SceneMananger(HWND hWnd);
	~SceneMananger();
	void Init();
	void Run();
	void Input();
	void Update();
	void Render();

public:
	void LoadImageData();
	void LoadLobbyData(const vector<pImageData>& lobbyDataVector);
	void LoadMapData();

};


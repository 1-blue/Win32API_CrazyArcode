#pragma once
#include "DataStruct.h"

class ImageManager;
class ObjectManager;
class LobbyUI;
class GameManager
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
	int stage;
	bool isFirst{ true };
	SelectData selectData{ 0 ,0, 0 };		//요거에 선택한 캐릭터들, 맵번호 넣음
	vector<LobbyUI*> LobbyDataVector;

public:
	GameManager(HWND hWnd);
	~GameManager();
	void Init();
	void Run();
	void Input();
	void Update();
	void Render();

public:
	void LoadImageData();
	void LoadLobbyData(const vector<pImageData>& lobbyDataVector);

};


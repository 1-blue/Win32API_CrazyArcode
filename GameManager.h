#pragma once
#include <Windows.h>

class ImageManager;
class ObjectManager;
class Character;
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

};


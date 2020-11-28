#pragma once
#include <Windows.h>

class ImageManager;
class ObjectManager;
class Character;
class GameManager
{
public:
	HWND hWnd;
	HDC hdc;
	HDC memDC;
	HDC memDCBack;
	HBITMAP hBitMap;
	HBITMAP oldHBitMap;
	ObjectManager* objectManager;
	ImageManager* imageManager;

	Character* player;
public:
	GameManager(HWND hWnd);
	~GameManager();
	void Init();
	void Run();
	void Render();


};


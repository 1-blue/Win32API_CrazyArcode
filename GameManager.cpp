#include "GameManager.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "Character.h"

GameManager::GameManager(HWND hWnd)
{
	this->hWnd = hWnd;
	this->hdc = GetDC(hWnd);
	objectManager = new ObjectManager();
	imageManager = new ImageManager();
}

GameManager::~GameManager()
{
	delete objectManager;
	delete imageManager;

	ReleaseDC(hWnd, hdc);
}

void GameManager::Init()
{
	imageManager->LoadData();
	objectManager->LoadCharacterData();
	memDC = CreateCompatibleDC(hdc);
	memDCBack = CreateCompatibleDC(hdc);

	player = dynamic_cast<Character*>(objectManager->Test());
	player->SetPosition({ 0,0 });
	player->SetSize({ 500,500 });
}

void GameManager::Run()
{
	Render();
}

void GameManager::Render()
{
	hBitMap = CreateCompatibleBitmap(hdc, 500, 500);
	hBitMap = player->GetHBitmap();
	oldHBitMap = (HBITMAP)SelectObject(memDCBack, hBitMap);
	
	player->Render(memDCBack, memDC);

	BitBlt(hdc, 0, 0, 500, 500, memDCBack, 0, 0, SRCCOPY);

	DeleteObject(oldHBitMap);
}
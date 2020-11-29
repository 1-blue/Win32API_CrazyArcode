#include "GameManager.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "Character.h"

GameManager::GameManager(HWND hWnd)
{
	this->hWnd = hWnd;
	this->hdc = GetDC(hWnd);
	objectManager->LoadCharacterData();
	memDC = CreateCompatibleDC(hdc);
	memDCBack = CreateCompatibleDC(hdc);
}

GameManager::~GameManager()
{
	delete objectManager;
	delete imageManager;

	DeleteDC(memDC);
	DeleteDC(memDCBack);
	ReleaseDC(hWnd, hdc);
}

void GameManager::Init()
{
	objectManager = new ObjectManager();
	imageManager = new ImageManager();

}

void GameManager::Run()
{
	Input();
	Update();
	Render();
}

void GameManager::Input()
{



}

void GameManager::Update()
{



}

void GameManager::Render()
{
	SelectObject(memDCBack, CreateCompatibleBitmap(hdc, WND_WIDTH, WND_HEIGHT));

	objectManager->Render(hdc, memDCBack, memDC);

	BitBlt(hdc, 0, 0, WND_WIDTH, WND_HEIGHT, memDCBack, 0, 0, SRCCOPY);
}

void GameManager::LoadBitmapData()
{
	imageManager->LoadData();
	objectManager->LoadDefaultData(imageManager->GetBitmap());

}

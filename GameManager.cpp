#include "GameManager.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "Character.h"

GameManager::GameManager(HWND hWnd)
{
	this->hWnd = hWnd;
	this->hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	memDCBack = CreateCompatibleDC(hdc);

	stage = GameStage::LOBBY;
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
	objectManager = new ObjectManager(&stage);
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
	objectManager->Input();
}

void GameManager::Update()
{
	objectManager->Update();
}

void GameManager::Render()
{
	if (oldHBitMap != NULL)
		DeleteObject(oldHBitMap);

	oldHBitMap = (HBITMAP)SelectObject(memDCBack, CreateCompatibleBitmap(hdc, WND_WIDTH, WND_HEIGHT));

	objectManager->Render(hdc, memDCBack, memDC);

	BitBlt(hdc, 0, 0, WND_WIDTH, WND_HEIGHT, memDCBack, 0, 0, SRCCOPY);
}

void GameManager::LoadImageData()
{
	imageManager->LoadImageData();
	objectManager->LoadLobbyData(imageManager->GetLobbyImageData());
	objectManager->LoadInGameImageData(imageManager->GetInGameImageData());
}

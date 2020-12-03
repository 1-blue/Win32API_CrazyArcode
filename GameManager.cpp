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

	//objectManager->LoadCharacterData();
}

void GameManager::Run()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		if(stage == 0)
			stage = 1;
		else if (stage == 1)
			stage = 0;
	}
	//테스트용으로 만든거
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
	objectManager->LoadDefaultData(imageManager->GetBitmap());
	objectManager->LoadInGameImageData(imageManager->GetInGameImageData());
}

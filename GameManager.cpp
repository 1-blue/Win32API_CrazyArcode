#include "GameManager.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "Character.h"
#include "MessageQueue.h"

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
	MessageQueue::RunEventQueue();
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

	//이것도 여기아닌데 일단 넣음
	if ((stage == GameStage::INGAME) && x == true)
	{
		objectManager->LoadRedCharacterImageData(imageManager->GetRedCharacterImageData(ObjectManager::selectData));
		objectManager->LoadBlueCharacterImageData(imageManager->GetBlueCharacterImageData(ObjectManager::selectData));
		x = false;
	}
}

void GameManager::LoadImageData()
{
	imageManager->LoadImageData();
	objectManager->LoadLobbyData(imageManager->GetLobbyImageData());
	objectManager->LoadInGameImageData(imageManager->GetInGameImageData());
}

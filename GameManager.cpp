#include "GameManager.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "MessageQueue.h"
#include "LobbyUI.h"

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

	for (auto objs : LobbyDataVector)
		delete objs;
	LobbyDataVector.clear();
}

void GameManager::Init()
{
	objectManager = new ObjectManager(&stage);
	imageManager = new ImageManager();
}

void GameManager::Run()
{
	Input();
	//MessageQueue::RunEventQueue();
	Update();
	Render();
}

void GameManager::Input()
{
	if (stage == GameStage::LOBBY)
	{
		for (const auto& lobby : LobbyDataVector)
			lobby->Input();
	}
	else if (stage == GameStage::INGAME)
		objectManager->Input();
}

void GameManager::Update()
{
	if (stage == GameStage::LOBBY)
	{
		for (const auto& lobby : LobbyDataVector)
			lobby->Update();
	}
	else if(stage == GameStage::INGAME)
		objectManager->Update();
}

void GameManager::Render()
{
	if (oldHBitMap != NULL)
		DeleteObject(oldHBitMap);

	oldHBitMap = (HBITMAP)SelectObject(memDCBack, CreateCompatibleBitmap(hdc, WND_WIDTH, WND_HEIGHT));

	if (stage == GameStage::LOBBY)
	{
		for (const auto& lobby : LobbyDataVector)
			lobby->Render(memDCBack, memDC);
	}
	else if (stage == GameStage::INGAME)
		objectManager->Render(hdc, memDCBack, memDC);

	BitBlt(hdc, 0, 0, WND_WIDTH, WND_HEIGHT, memDCBack, 0, 0, SRCCOPY);

	//게임시작버튼누르면
	if (LobbyUI::IsStart() && isFirst)
	{
		selectData.redCharacterNumber = LobbyUI::redImageNumber;
		selectData.blueCharacterNumber = LobbyUI::blueImageNumber;
		selectData.mapNumber = LobbyUI::mapImageNumber;
		objectManager->LoadRedCharacterImageData(imageManager->GetRedCharacterImageData(selectData));
		objectManager->LoadBlueCharacterImageData(imageManager->GetBlueCharacterImageData(selectData));
		objectManager->LoadRedCharacterStatsData(imageManager->GetRedCharacterStatsData(selectData));
		objectManager->LoadBlueCharacterStatsData(imageManager->GetBlueCharacterStatsData(selectData));
		isFirst = false;
		stage = GameStage::INGAME;
	}
}

void GameManager::LoadImageData()
{
	imageManager->LoadImageData();
	this->LoadLobbyData(imageManager->GetLobbyImageData());
	objectManager->LoadInGameImageData(imageManager->GetInGameImageData());
}

void GameManager::LoadLobbyData(const vector<pImageData>& lobbyDataVector)
{
	BITMAP bitMap;

	for (const auto iterator : lobbyDataVector)
	{
		GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);

		LobbyDataVector.emplace_back(new LobbyUI(iterator->name,
			{ iterator->x,iterator->y },
			{ bitMap.bmWidth ,bitMap.bmHeight },
			iterator->hNumber, iterator->vNumber,
			iterator->hBitmap));
	}
}

#include "GameMananger.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "MapManager.h"
#include "MessageQueue.h"
#include "LobbyScene.h"

GameMananger::GameMananger(HWND hWnd)
{
	//밑 4개 없애야할것들
	this->hWnd = hWnd;
	this->hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	memDCBack = CreateCompatibleDC(hdc);
	//=========================

	sceneManager = new SceneManager(hWnd);
	imageManager = new ImageManager();
	mapManager = new MapManager();


	stage = GameStage::LOBBY;
}

GameMananger::~GameMananger()
{
	delete sceneManager;
	delete imageManager;

	//밑에꺼 없애야할것들
	DeleteDC(memDC);
	DeleteDC(memDCBack);
	ReleaseDC(hWnd, hdc);

	for (auto& lobby : lobbyScene)
		delete lobby;
	lobbyScene.clear();
	//=====================
}

void GameMananger::Run()
{
	sceneManager->Process(stage);
	//MessageQueue::RunEventQueue();

	//밑에꺼 처리해야할것들
	Input();
	Update();
	Render();
	//=============
}

//sceneManager에서 3종세트 처리해야함,
void GameMananger::Input()
{
	if (stage == GameStage::LOBBY)
	{
		for (const auto& lobby : lobbyScene)
			lobby->Input();
	}
	else if (stage == GameStage::INGAME)
	{
		sceneManager->Input();
	}
}

void GameMananger::Update()
{
	if (stage == GameStage::LOBBY)
	{
		for (const auto& lobby : lobbyScene)
			lobby->Update();
	}
	else if (stage == GameStage::INGAME)
	{
		sceneManager->Update();
	}
}

void GameMananger::Render()
{
	if (oldHBitMap != NULL)
		DeleteObject(oldHBitMap);

	oldHBitMap = (HBITMAP)SelectObject(memDCBack, CreateCompatibleBitmap(hdc, WND_WIDTH, WND_HEIGHT));

	if (stage == GameStage::LOBBY)
	{
		for (const auto& lobby : lobbyScene)
			lobby->Render(memDCBack, memDC);
	}
	else if (stage == GameStage::INGAME)
	{
		sceneManager->Render(hdc, memDCBack, memDC);
	}

	BitBlt(hdc, 0, 0, WND_WIDTH, WND_HEIGHT, memDCBack, 0, 0, SRCCOPY);

	//게임시작버튼누르면
	if (LobbyScene::IsStart() && isFirst)
	{
		selectData.redCharacterNumber = LobbyScene::redImageNumber;
		selectData.blueCharacterNumber = LobbyScene::blueImageNumber;
		selectData.mapNumber = LobbyScene::mapImageNumber;
		sceneManager->LoadRedCharacterImageData(imageManager->GetRedCharacterImageData(selectData));
		sceneManager->LoadBlueCharacterImageData(imageManager->GetBlueCharacterImageData(selectData));
		sceneManager->LoadRedCharacterStatsData(imageManager->GetRedCharacterStatsData(selectData));
		sceneManager->LoadBlueCharacterStatsData(imageManager->GetBlueCharacterStatsData(selectData));
		sceneManager->LoadStaticObjectData(mapManager->LoadMap(selectData));
		isFirst = false;
		stage = GameStage::INGAME;
	}
}

void GameMananger::LoadImageData()
{
	imageManager->LoadImageData();
	this->LoadLobbyData(imageManager->GetLobbyImageData());
	sceneManager->LoadInGameImageData(imageManager->GetInGameImageData());
}

void GameMananger::LoadLobbyData(const vector<pImageData>& lobbyDataVector)
{
	BITMAP bitMap;

	for (const auto iterator : lobbyDataVector)
	{
		GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);

		lobbyScene.emplace_back(new LobbyScene(iterator->name,
			{ iterator->x,iterator->y },
			{ bitMap.bmWidth ,bitMap.bmHeight },
			iterator->hNumber, iterator->vNumber,
			iterator->hBitmap));
	}
}

void GameMananger::LoadMapData()
{
	mapManager->LoadTextMapData();
}

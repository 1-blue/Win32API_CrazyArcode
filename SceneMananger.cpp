#include "SceneMananger.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "MapManager.h"
#include "MessageQueue.h"
#include "LobbyScene.h"

SceneMananger::SceneMananger(HWND hWnd)
{
	this->hWnd = hWnd;
	this->hdc = GetDC(hWnd);
	memDC = CreateCompatibleDC(hdc);
	memDCBack = CreateCompatibleDC(hdc);

	stage = GameStage::LOBBY;
}

SceneMananger::~SceneMananger()
{
	delete objectManager;
	delete imageManager;

	DeleteDC(memDC);
	DeleteDC(memDCBack);
	ReleaseDC(hWnd, hdc);

	for (auto& lobby : lobbyScene)
		delete lobby;
	lobbyScene.clear();
}

void SceneMananger::Init()
{
	objectManager = new ObjectManager(&stage);
	imageManager = new ImageManager();
	mapManager = new MapManager();
}

void SceneMananger::Run()
{
	Input();
	//MessageQueue::RunEventQueue();
	Update();
	Render();
}

void SceneMananger::Input()
{
	if (stage == GameStage::LOBBY)
	{
		for (const auto& lobby : lobbyScene)
			lobby->Input();
	}
	else if (stage == GameStage::INGAME)
	{
		objectManager->Input();
	}
}

void SceneMananger::Update()
{
	if (stage == GameStage::LOBBY)
	{
		for (const auto& lobby : lobbyScene)
			lobby->Update();
	}
	else if (stage == GameStage::INGAME)
	{
		objectManager->Update();
	}
}

void SceneMananger::Render()
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
		objectManager->Render(hdc, memDCBack, memDC);
	}

	BitBlt(hdc, 0, 0, WND_WIDTH, WND_HEIGHT, memDCBack, 0, 0, SRCCOPY);

	//게임시작버튼누르면
	if (LobbyScene::IsStart() && isFirst)
	{
		selectData.redCharacterNumber = LobbyScene::redImageNumber;
		selectData.blueCharacterNumber = LobbyScene::blueImageNumber;
		selectData.mapNumber = LobbyScene::mapImageNumber;
		objectManager->LoadRedCharacterImageData(imageManager->GetRedCharacterImageData(selectData));
		objectManager->LoadBlueCharacterImageData(imageManager->GetBlueCharacterImageData(selectData));
		objectManager->LoadRedCharacterStatsData(imageManager->GetRedCharacterStatsData(selectData));
		objectManager->LoadBlueCharacterStatsData(imageManager->GetBlueCharacterStatsData(selectData));
		objectManager->LoadStaticObjectData(mapManager->LoadMap(selectData));
		isFirst = false;
		stage = GameStage::INGAME;
	}
}

void SceneMananger::LoadImageData()
{
	imageManager->LoadImageData();
	this->LoadLobbyData(imageManager->GetLobbyImageData());
	objectManager->LoadInGameImageData(imageManager->GetInGameImageData());
}

void SceneMananger::LoadLobbyData(const vector<pImageData>& lobbyDataVector)
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

void SceneMananger::LoadMapData()
{
	mapManager->LoadTextMapData();
}

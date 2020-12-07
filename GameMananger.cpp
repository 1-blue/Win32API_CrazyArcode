#include "GameMananger.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "MapManager.h"
#include "MessageQueue.h"

extern bool isGameStart;

GameMananger::GameMananger(HWND hWnd)
{
	sceneManager = new SceneManager(hWnd);
	imageManager = new ImageManager();
	mapManager = new MapManager();

	stage = GameStage::LOBBY;
}

GameMananger::~GameMananger()
{
	delete sceneManager;
	delete imageManager;
	delete mapManager;
}

void GameMananger::Run()
{
	if (isGameStart && isFirst)
	{
		stage = GameStage::INGAME;
		sceneManager->Process(stage);
		sceneManager->LoadInGameBackGroundImage(imageManager->GetInGameBackGroundImage());
		sceneManager->LoadCharacterData(imageManager->GetCharacterImageData(sceneManager->GetSelectData()), imageManager->GetCharacterStatsData(sceneManager->GetSelectData()));
		sceneManager->LoadMapData(mapManager->LoadMap(sceneManager->GetSelectData()));
		sceneManager->LoadWaterBallonData(imageManager->GetWaterBallonImageData());

		isFirst = false;
	}

	sceneManager->Process(stage);
	//MessageQueue::RunEventQueue();
}

void GameMananger::LoadImageData()
{
	imageManager->LoadImageData();
	sceneManager->LoadLobbyData(imageManager->GetLobbyImageData());
}

void GameMananger::LoadMapData()
{
	mapManager->LoadTextMapData();
}

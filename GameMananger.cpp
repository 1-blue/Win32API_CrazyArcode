#include "GameMananger.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "MapManager.h"

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
	sceneManager->Process(stage);

	if (sceneManager->GetSelectData().isStart && isFirst)
		stage = GameStage::INGAME_LOADING;

	if (stage == GameStage::INGAME_LOADING && isFirst)
		LoadInGameData();
}

void GameMananger::LoadLobbyData()
{
	imageManager->LoadImageData();
	sceneManager->LoadLobbyData(imageManager->GetLobbyImageData());
}

void GameMananger::LoadInGameData()
{
	stage = GameStage::INGAME;
	isFirst = false;
	sceneManager->LoadInGameBackGroundImage(imageManager->GetInGameBackGroundImage());
	sceneManager->LoadCharacterData(imageManager->GetCharacterImageData(sceneManager->GetSelectData()), imageManager->GetCharacterStatsData(sceneManager->GetSelectData()));
	sceneManager->LoadMapData(mapManager->LoadMap(sceneManager->GetSelectData()));
	sceneManager->LoadWaterBallonData(imageManager->GetWaterBallonImageData());
}

void GameMananger::LoadMapData()
{
	mapManager->LoadTextMapData();
}

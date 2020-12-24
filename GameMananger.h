#pragma once
#include "DataStruct.h"

class SceneManager;
class ImageManager;
class MapManager;
class SoundManager;
class GameMananger
{
private:
	SceneManager* sceneManager{ NULL };
	ImageManager* imageManager{ NULL };
	MapManager* mapManager{ NULL };
	SoundManager* soundManager{ NULL };

public:
	GameMananger(HWND hWnd);
	~GameMananger();

public:
	void Run();
	void LoadLobbyData();
	void LoadInGameData();
	void LoadMapData();

};


#pragma once
#include "DataStruct.h"

class SceneManager;
class ImageManager;
class MapManager;
class GameMananger
{
private:
	SceneManager* sceneManager{ NULL };
	ImageManager* imageManager{ NULL };
	MapManager* mapManager{ NULL };
	int stage;
	bool isFirst{ true };

public:
	GameMananger(HWND hWnd);
	~GameMananger();

public:
	void Run();
	void LoadImageData();
	void LoadMapData();

};


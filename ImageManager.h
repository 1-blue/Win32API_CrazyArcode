#pragma once
#pragma comment(lib, "Msimg32.lib")
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include "DataStruct.h"

using namespace std;

class ImageManager
{
private:
	ifstream fin;
	vector<pImageData2> lobbyBitmap;
	vector<pImageData> InGameImageInfo;

	//추가
	vector<pImageData2> characterImageData;
	pImageData2 redCharacter;
	pImageData2 blueCharacter;


public:
	ImageManager();
	~ImageManager();

	void LoadImageData();
	void LoadLobbyImageData();
	void LoadInGameImageData();

	//추가
	void LoadCharacterImageData();
	const pImageData2& GetRedCharacterImage(SelectData d) const;
	const pImageData2& GetBlueCharacterImage(SelectData d) const;
	const vector<pImageData2>& GetBitmap() const;


	const vector<pImageData>& GetInGameImageData();
};


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
	vector<pImageData> lobbyBitmap;
	vector<pImageData> InGameImageInfo;
	vector<pImageData> characterData;

public:
	ImageManager();
	~ImageManager();

	void LoadImageData();
	void LoadTextImageData(const string path, vector<pImageData>& data);

	const vector<pImageData>& GetLobbyImageData() const;
	const vector<pImageData>& GetInGameImageData() const;
	const pImageData GetRedCharacterImageData(SelectData selectData) const;
	const pImageData GetBlueCharacterImageData(SelectData selectData) const;

};


#pragma once
#pragma comment(lib, "Msimg32.lib")
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include "DataStruct.h"
#include <ctime>

using namespace std;

class ImageManager
{
private:
	ifstream fin;
	vector<pImageData> lobbyBitmap;
	vector<pImageData> InGameImageInfo;
	vector<pImageData> characterImageData;
	vector<CharacterStatsData> characterStatsData;

public:
	ImageManager();
	~ImageManager();

	void LoadImageData();
	void LoadTextImageData(const string path, vector<pImageData>& data);
	void LoadTextStatsData(const string path, vector<CharacterStatsData>& data);

	const vector<pImageData>& GetLobbyImageData() const;
	const vector<pImageData>& GetInGameImageData() const;
	const pImageData GetRedCharacterImageData(const SelectData& selectData) const;
	const pImageData GetBlueCharacterImageData(const SelectData& selectData) const;
	const CharacterStatsData GetRedCharacterStatsData(const SelectData& selectData) const;
	const CharacterStatsData GetBlueCharacterStatsData(const SelectData& selectData) const;

};


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
	pImageData character[PLAYER_NUMBER]{ NULL };		//선택한 캐릭터이미지를 넘겨줄때 사용
	vector<CharacterStatsData> characterStatsData;
	CharacterStatsData temp[PLAYER_NUMBER]{ NULL };		//선택한 캐릭터 스텟을 넘겨줄때 사용

public:
	ImageManager();
	~ImageManager();

	void LoadImageData();
	void LoadTextImageData(const string path, vector<pImageData>& data);
	void LoadTextImageData(const string path, pImageData& data);		//단일 이미지 전용
	void LoadTextStatsData(const string path, vector<CharacterStatsData>& data);

	const vector<pImageData>& GetLobbyImageData() const;

	const vector<pImageData>& GetInGameImage() const;
	const pImageData* GetCharacterImageData(const SelectData& selectData);

	const CharacterStatsData* GetCharacterStatsData(const SelectData& selectData);
};


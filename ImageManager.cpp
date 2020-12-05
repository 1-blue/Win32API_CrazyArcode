#include "ImageManager.h"

ImageManager::ImageManager()
{

}

ImageManager::~ImageManager()
{
	for (auto bitmap : lobbyBitmap)
		delete bitmap;
	lobbyBitmap.clear();

	for (auto bitmap : InGameImageInfo)
		delete bitmap;
	InGameImageInfo.clear();

	for (auto bitmap : characterImageData)
		delete bitmap;
	characterImageData.clear();
}

void ImageManager::LoadImageData()
{
	LoadTextImageData("data_char\\LobbyImageData.txt", lobbyBitmap);
	LoadTextImageData("data_char\\InGameImageData.txt", InGameImageInfo);
	LoadTextImageData("data_char\\CharacterImageData.txt", characterImageData);
	LoadTextStatsData("data_char\\CharacterStatsData.txt", characterStatsData);
}

void ImageManager::LoadTextImageData(string path, vector<pImageData>& data)
{
	fin.open(path);
	string str[IMAGE_DATA_LENGTH];
	for (int i = 0; i < 2; i++)
		getline(fin, str[0]);	//첫 2줄은 설명이라서 읽고버림

	while (!fin.eof())
	{
		for (int i = 0; i < IMAGE_DATA_LENGTH; i++)
			fin >> str[i];

		data.emplace_back(new ImageData{
			str[0],			//이름저장
			(HBITMAP)LoadImage(NULL, str[1].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION),	//비트맵저장
			stoi(str[2]),	//Object종류구분
			stoi(str[3]),	//x좌표
			stoi(str[4]),	//y좌표
			stoi(str[5]),	//가로이미지수
			stoi(str[6]),	//세로이미지수
			});
	}
	fin.close();
}

void ImageManager::LoadTextStatsData(const string path, vector<CharacterStatsData>& data)
{
	fin.open(path);
	string str[STATS_DATA_LENGTH];
	for (int i = 0; i < 2; i++)
		getline(fin, str[0]);	//첫 2줄은 설명이라서 읽고버림

	while (!fin.eof())
	{
		for (int i = 0; i < STATS_DATA_LENGTH; i++)
			fin >> str[i];

		data.emplace_back(CharacterStatsData{
			stoi(str[1]),	//초기풍선개수
			stoi(str[2]),	//최대풍선개수
			stoi(str[3]),	//초기풍선길이
			stoi(str[4]),	//최대풍선길이
			stoi(str[5]),	//초기이동속도
			stoi(str[6]),	//최대이동속도
			});
	}
	fin.close();
}

const vector<pImageData>& ImageManager::GetLobbyImageData() const
{
	return lobbyBitmap;
}

const vector<pImageData>& ImageManager::GetInGameImageData() const
{
	return InGameImageInfo;
}

const pImageData ImageManager::GetRedCharacterImageData(const SelectData& selectData) const
{
	pImageData character = NULL;
	srand((unsigned int)GetTickCount64());
	int idx = rand() % 2;

	switch (selectData.redCharacterNumber)
	{
	case CharacterSelect::BAZZI:
		character = characterImageData[0];
		break;

	case CharacterSelect::DIZNI:
		character = characterImageData[1];
		break;

	default:
		character = characterImageData[idx];
		break;
	}

	return character;
}

const pImageData ImageManager::GetBlueCharacterImageData(const SelectData& selectData) const
{
	pImageData character = NULL;
	srand((unsigned int)GetTickCount64());
	int idx = rand() % 2 + 2;

	switch (selectData.blueCharacterNumber)
	{
	case CharacterSelect::BAZZI:
		character = characterImageData[2];
		break;

	case CharacterSelect::DIZNI:
		character = characterImageData[3];
		break;

	default:
		character = characterImageData[idx];
		break;
	}

	return character;
}

const CharacterStatsData ImageManager::GetRedCharacterStatsData(const SelectData& selectData) const
{
	CharacterStatsData temp{ NULL };

	switch (selectData.redCharacterNumber)
	{
	case CharacterSelect::BAZZI:
		temp = characterStatsData[0];
		break;

	case CharacterSelect::DIZNI:
		temp = characterStatsData[1];
		break;
	}

	return temp;
}

const CharacterStatsData ImageManager::GetBlueCharacterStatsData(const SelectData& selectData) const
{
	CharacterStatsData temp{ NULL };

	switch (selectData.blueCharacterNumber)
	{
	case CharacterSelect::BAZZI:
		temp = characterStatsData[0];
		break;

	case CharacterSelect::DIZNI:
		temp = characterStatsData[1];
		break;
	}

	return temp;
}

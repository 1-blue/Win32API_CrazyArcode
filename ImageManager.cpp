#include "ImageManager.h"
#include "MessageQueue.h"

ImageManager::ImageManager()
{

}

ImageManager::~ImageManager()
{
	for (const auto& bitmap : lobbyBitmap)
		delete bitmap;
	lobbyBitmap.clear();

	for (const auto& bitmap : InGameImageInfo)
		delete bitmap;
	InGameImageInfo.clear();

	for (const auto& bitmap : characterImageData)
		delete bitmap;
	characterImageData.clear();
}

void ImageManager::LoadImageData()
{
	//이 텍스트파일 path들도 하나의 텍스트파일에 모아서 읽어서 쓸까??
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
			MessageQueue::StringToEnum(str[0]),			//이름저장
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

void ImageManager::LoadTextImageData(const string path, pImageData& data)
{
	fin.open(path);
	string str[IMAGE_DATA_LENGTH];
	for (int i = 0; i < 2; i++)
		getline(fin, str[0]);	//첫 2줄은 설명이라서 읽고버림

	for (int i = 0; i < IMAGE_DATA_LENGTH; i++)
		fin >> str[i];

	data = new ImageData{
		MessageQueue::StringToEnum(str[0]),			//이름저장
		(HBITMAP)LoadImage(NULL, str[1].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION),	//비트맵저장
		stoi(str[2]),	//Object종류구분
		stoi(str[3]),	//x좌표
		stoi(str[4]),	//y좌표
		stoi(str[5]),	//가로이미지수
		stoi(str[6]),	//세로이미지수
		};
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

const vector<pImageData>& ImageManager::GetInGameImage() const
{
	return InGameImageInfo;
}

const pImageData* ImageManager::GetCharacterImageData(const SelectData& selectData)
{
	srand((unsigned int)time(NULL));
	int idx = rand() % 2;

	switch (selectData.redCharacterNumber)
	{
	case CharacterSelect::BAZZI:
		character[0] = characterImageData[0];
		break;

	case CharacterSelect::DIZNI:
		character[0] = characterImageData[1];
		break;

	default:
		character[0] = characterImageData[idx];
		break;
	}

	switch (selectData.blueCharacterNumber)
	{
	case CharacterSelect::BAZZI:
		character[1] = characterImageData[2];
		break;

	case CharacterSelect::DIZNI:
		character[1] = characterImageData[3];
		break;

	default:
		idx = rand() % 2;

		character[1] = characterImageData[idx + 2];		//수정필요.. 랜덤일때 난수발생..
		break;
	}

	character[2] = characterImageData[4];		//Trapped
	character[3] = characterImageData[5];		//Die

	return character;
}

const CharacterStatsData* ImageManager::GetCharacterStatsData(const SelectData& selectData)
{
	switch (selectData.redCharacterNumber)
	{
	case CharacterSelect::BAZZI:
		temp[0] = characterStatsData[0];
		break;

	case CharacterSelect::DIZNI:
		temp[0] = characterStatsData[1];
		break;
	}

	switch (selectData.blueCharacterNumber)
	{
	case CharacterSelect::BAZZI:
		temp[1] = characterStatsData[0];
		break;

	case CharacterSelect::DIZNI:
		temp[1] = characterStatsData[1];
		break;
	}

	return temp;
}
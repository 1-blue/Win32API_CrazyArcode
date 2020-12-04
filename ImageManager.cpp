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

	for (auto bitmap : characterData)
		delete bitmap;
	characterData.clear();
}

void ImageManager::LoadImageData()
{
	LoadTextImageData("data_char\\LobbyImageData.txt", lobbyBitmap);
	LoadTextImageData("data_char\\InGameImageData.txt", InGameImageInfo);
	LoadTextImageData("data_char\\CharacterImageData.txt", characterData);
}

void ImageManager::LoadTextImageData(string path, vector<pImageData>& data)
{
	fin.open(path);
	string str[ImageDataLength];
	for (int i = 0; i < 2; i++)
		getline(fin, str[0]);	//첫 2줄은 설명이라서 읽고버림

	while (!fin.eof())
	{
		for (int i = 0; i < ImageDataLength; i++)
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

const vector<pImageData>& ImageManager::GetLobbyImageData() const
{
	return lobbyBitmap;
}

const vector<pImageData>& ImageManager::GetInGameImageData() const
{
	return InGameImageInfo;
}

const pImageData ImageManager::GetRedCharacterImageData(SelectData selectData) const
{
	pImageData character = NULL;

	switch (selectData.redCharacterNumber)
	{
	case CharacterSelect::BAZZI:
		character = characterData[0];
		break;
	case CharacterSelect::DIZNI:
		character = characterData[1];
		break;
		//랜덤인경우 랜덤으로 넣는기능추가하기
	}

	return character;
}

const pImageData ImageManager::GetBlueCharacterImageData(SelectData selectData) const
{
	pImageData character = NULL;

	switch (selectData.blueCharacterNumber)
	{
	case CharacterSelect::BAZZI:
		character = characterData[2];
		break;
	case CharacterSelect::DIZNI:
		character = characterData[3];
		break;
		//랜덤인경우 랜덤으로 넣는기능추가하기
	}

	return character;
}

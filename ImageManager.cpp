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
}

void ImageManager::LoadImageData()
{
	LoadLobbyData();
	LoadInGameImageData();
}

void ImageManager::LoadLobbyData()
{
	//여기서 default데이터 이름과 path 저장
	fin.open("data_char\\LobbyImageData.txt");
	string str[SSSS - 1];
	for(int i=0; i<2; i++)
		getline(fin, str[0]);	//첫 2줄은 설명이라서 읽고버림

	while (!fin.eof())
	{
		for (int i = 0; i < SSSS - 1; i++)
			fin >> str[i];

		lobbyBitmap.emplace_back(new ImageData2{
			str[0],			//이름저장
			(HBITMAP)LoadImage(NULL, str[1].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION),	//비트맵저장
			stoi(str[2]),	//Object종류구분
			stoi(str[3]),	//x좌표
			stoi(str[4]),	//y좌표
			stoi(str[5]),	//가로이미지수
			stoi(str[6]),	//세로이미지수
			0,				//가로간격.. 간격은 나중에 계산
			0,				//세로간격
			});
	}
	fin.close();
}

void ImageManager::LoadInGameImageData()
{
	fin.open("data_char\\InGameImageData.txt");
	string str[SSSS];
	for (int i = 0; i < 2; i++)
		getline(fin, str[0]);	//첫줄은 설명이라서 읽고버림

	while (!fin.eof())
	{
		for (int i = 0; i < SSSS; i++)
			fin >> str[i];

		InGameImageInfo.emplace_back(new ImageData{
			str[0],			//이름저장
			(HBITMAP)LoadImage(NULL, str[1].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION),	//비트맵저장
			stoi(str[2]),	//Object종류구분
			stoi(str[3]),	//x좌표
			stoi(str[4]),	//y좌표
			stoi(str[5]),	//단일, 가로. 세로 구분
			stoi(str[6]),	//이미지수
			stoi(str[7]),	//간격
			});
	}
	fin.close();
}

const vector<pImageData2>& ImageManager::GetLobbyImageData() const
{
	return lobbyBitmap;
}

const vector<pImageData>& ImageManager::GetInGameImageData()
{
	return InGameImageInfo;
}

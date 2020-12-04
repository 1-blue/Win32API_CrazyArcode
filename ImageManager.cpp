#include "ImageManager.h"

ImageManager::ImageManager()
{
	redCharacter = new ImageData2();
	blueCharacter = new ImageData2();
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
	LoadLobbyImageData();
	LoadInGameImageData();
	LoadCharacterImageData();
}

void ImageManager::LoadLobbyImageData()
{
	//여기서 default데이터 이름과 path 저장
	fin.open("data_char\\LobbyImageData.txt");
	string str[SSSS];
	for(int i=0; i<2; i++)
		getline(fin, str[0]);	//첫줄은 설명이라서 읽고버림

	while (!fin.eof())
	{
		for (int i = 0; i < SSSS; i++)
			fin >> str[i];

		lobbyBitmap.emplace_back(new ImageData2{
			str[0],			//이름저장
			(HBITMAP)LoadImage(NULL, str[1].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION),	//비트맵저장
			stoi(str[2]),	//Object종류구분
			stoi(str[3]),	//x좌표
			stoi(str[4]),	//y좌표
			stoi(str[5]),	//가로이미지수
			stoi(str[6]),	//세로이미지수
			0,				//가로간격.. 뒤에서 계산
			0				//세로간격
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

void ImageManager::LoadCharacterImageData()
{
	fin.open("data_char\\CharacterImageData.txt");
	string str[SSSS - 1];
	for (int i = 0; i < 2; i++)
		getline(fin, str[0]);	//첫줄은 설명이라서 읽고버림

	while (!fin.eof())
	{
		for (int i = 0; i < SSSS - 1; i++)
			fin >> str[i];

		characterImageData.emplace_back(new ImageData2{
			str[0],			//이름저장
			(HBITMAP)LoadImage(NULL, str[1].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION),	//비트맵저장
			stoi(str[2]),	//Object종류구분
			stoi(str[3]),	//x좌표
			stoi(str[4]),	//y좌표
			stoi(str[5]),	//가로이미지수
			stoi(str[6]),	//세로이미지수
			0,				//가로간격.. 뒤에서 계산
			0				//세로간격
			});
	}
	fin.close();
}

const pImageData2& ImageManager::GetRedCharacterImage(SelectData d) const
{
	BITMAP bmp;

	switch (d.redCharacterNumber)
	{
	case CharacterSelect::BAZZI:
		GetObject(characterImageData[0]->hBitmap, sizeof(BITMAP), &bmp);	
		redCharacter->name = characterImageData[0]->name;							//이름
		redCharacter->hBitmap = characterImageData[0]->hBitmap;						//비트맵
		redCharacter->x = characterImageData[0]->x;									//출력x좌표
		redCharacter->y = characterImageData[0]->y;									//출력y좌표
		redCharacter->hNumber = characterImageData[0]->hNumber;						//가로이미지수
		redCharacter->vNumber = characterImageData[0]->vNumber;						//세로이미지수
		redCharacter->hInterval = bmp.bmWidth / characterImageData[0]->vNumber;		//가로간격 : 가로이미지수 / 가로길이
		redCharacter->vInterval = bmp.bmHeight / characterImageData[0]->hNumber;	//세로간격 : 세로이미지수 / 세로길이
		break;

	case CharacterSelect::DIZNI:
		GetObject(characterImageData[1]->hBitmap, sizeof(BITMAP), &bmp);
		redCharacter->name = characterImageData[1]->name;							//이름
		redCharacter->hBitmap = characterImageData[1]->hBitmap;						//비트맵
		redCharacter->x = characterImageData[1]->x;									//출력x좌표
		redCharacter->y = characterImageData[1]->y;									//출력y좌표
		redCharacter->hNumber = characterImageData[1]->hNumber;						//가로이미지수
		redCharacter->vNumber = characterImageData[1]->vNumber;						//세로이미지수
		redCharacter->hInterval = bmp.bmWidth / characterImageData[1]->vNumber;		//가로간격 : 가로이미지수 / 가로길이
		redCharacter->vInterval = bmp.bmHeight / characterImageData[1]->hNumber;	//세로간격 : 세로이미지수 / 세로길이
		break;
	}

	return redCharacter;
}

const pImageData2& ImageManager::GetBlueCharacterImage(SelectData d) const
{
	BITMAP bmp;

	switch (d.blueCharacterNumber)
	{
	case CharacterSelect::BAZZI:
		GetObject(characterImageData[2]->hBitmap, sizeof(BITMAP), &bmp);
		blueCharacter->name = characterImageData[2]->name;							//이름
		blueCharacter->hBitmap = characterImageData[2]->hBitmap;					//비트맵
		blueCharacter->x = characterImageData[2]->x;								//출력x좌표
		blueCharacter->y = characterImageData[2]->y;								//출력y좌표
		blueCharacter->hNumber = characterImageData[2]->hNumber;					//가로이미지수
		blueCharacter->vNumber = characterImageData[2]->vNumber;					//세로이미지수
		blueCharacter->hInterval = bmp.bmWidth / characterImageData[2]->vNumber;	//가로간격 : 가로이미지수 / 가로길이
		blueCharacter->vInterval = bmp.bmHeight / characterImageData[2]->hNumber;	//세로간격 : 세로이미지수 / 세로길이
		break;

	case CharacterSelect::DIZNI:
		GetObject(characterImageData[3]->hBitmap, sizeof(BITMAP), &bmp);
		redCharacter->name = characterImageData[3]->name;							//이름
		redCharacter->hBitmap = characterImageData[3]->hBitmap;						//비트맵
		redCharacter->x = characterImageData[3]->x;									//출력x좌표
		redCharacter->y = characterImageData[3]->y;									//출력y좌표
		redCharacter->hNumber = characterImageData[3]->hNumber;						//가로이미지수
		redCharacter->vNumber = characterImageData[3]->vNumber;						//세로이미지수
		redCharacter->hInterval = bmp.bmWidth / characterImageData[3]->vNumber;		//가로간격 : 가로이미지수 / 가로길이
		redCharacter->vInterval = bmp.bmHeight / characterImageData[3]->hNumber;	//세로간격 : 세로이미지수 / 세로길이
		break;
	}

	return blueCharacter;
}

const vector<pImageData2>& ImageManager::GetBitmap() const
{
	return lobbyBitmap;
}

const vector<pImageData>& ImageManager::GetInGameImageData()
{
	return InGameImageInfo;
}

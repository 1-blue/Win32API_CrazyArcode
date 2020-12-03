#include "ImageManager.h"

ImageManager::ImageManager()
{

}

ImageManager::~ImageManager()
{
	for (auto bitmap : defaultBitmap)
		delete bitmap;
	defaultBitmap.clear();
}

void ImageManager::LoadDafaultData()
{
	//여기서 default데이터 이름과 path 저장
	fin.open("data_char\\DefaultData.txt");
	string str[SSSS];
	for(int i=0; i<2; i++)
		getline(fin, str[0]);	//첫줄은 설명이라서 읽고버림

	while (!fin.eof())
	{
		for (int i = 0; i < SSSS; i++)
			fin >> str[i];

		defaultBitmap.emplace_back(new DefaultData{
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
}

const vector<pDefaultData>& ImageManager::GetBitmap() const
{
	return defaultBitmap;
}

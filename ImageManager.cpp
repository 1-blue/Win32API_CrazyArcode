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

void ImageManager::LoadData()
{
	//여기서 default데이터 이름과 path 저장
	fin.open("data_char\\DefaultData.txt");
	string str[SSSS];

	//str[0] => name
	//str[1] => path
	while (!fin.eof())
	{
		for (int i = 0; i < SSSS; i++)
			fin >> str[i];

		defaultBitmap.emplace_back(new DefaultBitmap{
			str[0],	//이름저장
			(HBITMAP)LoadImage(NULL, str[1].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION),	//비트맵저장
			stoi(str[2]),stoi(str[3]),stoi(str[4])
			});
	}
}

const vector<pDefaultBitmap>& ImageManager::GetBitmap() const
{
	return defaultBitmap;
}

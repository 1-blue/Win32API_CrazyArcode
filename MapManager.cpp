#include "MapManager.h"

void MapManager::LoadTextMapData()
{
	fin.open("data_char\\MapData.txt");
	string str[2];
	for (int i = 0; i < 2; i++)
		getline(fin, str[0]);	//첫 2줄은 설명이라서 읽고버림

	while (!fin.eof())
	{
		for (int i = 0; i < 2; i++)
			fin >> str[i];

		mapData.emplace_back(MapData{
			str[0],		//맵이름
			str[1],		//경로
			NULL		//맵정보.. 뒤에서 저장
			});
	}
	fin.close();
}

const MapData& MapManager::LoadMap(SelectData selectData)
{
	char x;
	int widx = 0;
	int hidx = 0;

	fin.open(mapData[selectData.mapNumber].path);		//맵이름에 맞는 경로의 txt파일열고
	hidx = 0;											//0=>공백 1=>블럭 2=>벽
	widx = 0;
	while (!fin.eof())
	{
		fin.get(x);
		if (x == '\n')
		{
			hidx++;
			widx = 0;
		}
		else
		{
			mapData[selectData.mapNumber].data[hidx][widx++] = static_cast<int>(x) - 48;
		}
	}
	fin.close();

	return mapData[selectData.mapNumber];
}

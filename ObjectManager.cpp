#include "ObjectManager.h"
#include "Obj.h"
#include "Character.h"
#include <sstream>

extern HWND hWnd;

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	for (auto character : characterDataVector)
		delete character;
	characterDataVector.clear();

	for (auto monster : monsterDataVector)
		delete monster;
	monsterDataVector.clear();

	for (auto block : blockDataVector)
		delete block;
	blockDataVector.clear();

	for (auto item : itemDataVector)
		delete item;
	itemDataVector.clear();

	for (auto object : objectList)
		delete object;
	objectList.clear();

	for (auto hbmp : hbmpList)
		delete hbmp;
	hbmpList.clear();
}

void ObjectManager::GetImageDataList(list<HBITMAP>* imageDataList)
{
	hbmpList = *imageDataList;
}

void ObjectManager::LoadCharacterData()
{
	string data[8];

	fin.open("data_char\\data.txt");
	getline(fin, data[0]);
	while (!fin.eof())
	{
		for (int i = 0; i < 8; i++)
			fin >> data[i];

		characterDataVector.emplace_back(new Character(CHARTERDATA
			{data[0],stoi(data[1]),stoi(data[2]),stoi(data[3]),
			stoi(data[4]),stoi(data[5]),stoi(data[6]), stoi(data[7])} ));
	}
	fin.close();


	fin.open("data_char\\image_data.txt");
	getline(fin, data[0]);	//값 제거
	while (!fin.eof())
	{
		fin >> data[0];	//값 제거
		fin >> data[0];	//사용할 값

		imageVector.emplace_back(data[0]);
	}
	fin.close();	

	
	int i = 0;
	for (auto iterator : characterDataVector)
	{
		iterator->SetHBitmap((HBITMAP)LoadImage(NULL, imageVector[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
		i++;
	}
}

void ObjectManager::LoadMonsterData()
{
}

void ObjectManager::LoadBlockData()
{
}

void ObjectManager::LoadItemData()
{
}

Obj* ObjectManager::Test()
{
	return characterDataVector[0];
}

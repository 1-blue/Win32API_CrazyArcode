#include "ObjectManager.h"
#include "Obj.h"
#include "StaticObject.h"
#include "Character.h"
#include <sstream>

extern HWND hWnd;


void ObjectManager::Render(HDC hdc, HDC memDCBack, HDC memDC)
{
	for (auto it = objectVector.begin(); it != objectVector.end(); it++)
	{
		if (it != objectVector.end() - 1)
		{
			(*it)->Render(memDCBack, memDC);
		}
		else
			(*it)->Rendert(memDCBack, memDC);
	}


	/*for (auto iterator : objectVector)
	{
		iterator->Render(memDCBack, memDC);
	}*/

	//BitBlt(memDC, defaultData[i].location.x, defaultData[i].location.y, bitmap.bmWidth, bitmap.bmHeight, memDCBack, 0, 0, SRCCOPY);
	
	////for (int i = 0; i < defaultBitmap.size(); i++)
	////{
	//	GetObject(defaultBitmap[2]->hBitmap, sizeof(BITMAP), &tempBitmap);
	//	SelectObject(memDCBack, defaultBitmap[2]->hBitmap);
	//	//BitBlt(memDC, defaultData[i].location.x, defaultData[i].location.y, bitmap.bmWidth, bitmap.bmHeight, memDCBack, 0, 0, SRCCOPY);
	//	TransparentBlt(memDC, defaultBitmap[2]->location.x, defaultBitmap[2]->location.y, tempBitmap.bmWidth, tempBitmap.bmHeight, memDCBack, 0, 0, tempBitmap.bmWidth, tempBitmap.bmHeight, RGB(255, 0, 255));
	//	//GdiTransparentBlt(memDC, defaultBitmap[8]->location.x, defaultBitmap[8]->location.y, tempBitmap.bmWidth, tempBitmap.bmHeight / 2, memDCBack, 0, 0, tempBitmap.bmWidth, tempBitmap.bmHeight, RGB(255, 0, 255));
	////}
	////TransparentBlt배경색 지우기
	////BitBlt대신 사용
}

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
	for (auto objs : objectVector)
		delete objs;
	objectVector.clear();

	/*
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
	hbmpList.clear();*/
}

void ObjectManager::GetImageDataList(list<HBITMAP>* imageDataList)
{
	hbmpList = *imageDataList;
}

void ObjectManager::LoadCharacterData()
{
	//string data[8];

	//fin.open("data_char\\data.txt");
	//getline(fin, data[0]);
	//while (!fin.eof())
	//{
	//	for (int i = 0; i < 8; i++)
	//		fin >> data[i];

	//	characterDataVector.emplace_back(new Character(
	//		{data[0],stoi(data[1]),stoi(data[2]),stoi(data[3]),
	//		stoi(data[4]),stoi(data[5]),stoi(data[6]), stoi(data[7])} ));
	//}
	//fin.close();

	//fin.open("data_char\\image_data.txt");
	//getline(fin, data[0]);	//값 제거 (설명)
	//while (!fin.eof())
	//{
	//	fin >> data[0];	//값 제거 (인덱스)
	//	fin >> data[0];	//사용할 값 (이미지 path)

	//	imagePathVector.emplace_back(data[0]);
	//}
	//fin.close();	
	//
	//int i = 0;
	//for (auto iterator : characterDataVector)
	//{
	//	iterator->SetHBitmap((HBITMAP)LoadImage(NULL, imagePathVector[i].c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION));
	//	i++;
	//}
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

void ObjectManager::LoadDefaultData(const vector<pDefaultBitmap>& bitmapVector)
{
	BITMAP bitMap;
	this->bitmapVector = bitmapVector;

	for (auto iterator : bitmapVector)
	{
		if (iterator->objType == 0)
		{
			GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);
				
			objectVector.emplace_back(new StaticObject({ iterator->x,iterator->y }, { bitMap.bmWidth ,bitMap.bmHeight }, iterator->hBitmap));
		}

	}
}

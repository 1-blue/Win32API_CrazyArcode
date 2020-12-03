#include "ObjectManager.h"
#include "Obj.h"
#include "Character.h"
#include "WaitingUI.h"

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

void ObjectManager::Input()
{
	for (auto it = objectVector.begin(); it != objectVector.end(); it++)
		(*it)->Input();
}

void ObjectManager::Update()
{
	for (auto it = objectVector.begin(); it != objectVector.end(); it++)
		(*it)->Update();
}

void ObjectManager::Render(HDC hdc, HDC memDCBack, HDC memDC)
{
	for (auto it = objectVector.begin(); it != objectVector.end(); it++)
		(*it)->Render(memDCBack, memDC);
}

void ObjectManager::LoadDefaultData(const vector<pDefaultData>& bitmapVector)
{
	BITMAP bitMap;
	this->bitmapVector = bitmapVector;

	for (auto iterator : bitmapVector)
	{
		if (iterator->objType == 0)
		{
			GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);

			objectVector.emplace_back(new WaitingUI(iterator->name, { iterator->x,iterator->y }, { bitMap.bmWidth ,bitMap.bmHeight }, iterator->kinds, iterator->number, iterator->interval, iterator->hBitmap));
			defaultDataVector.emplace_back(new WaitingUI(iterator->name, { iterator->x,iterator->y }, { bitMap.bmWidth ,bitMap.bmHeight }, iterator->kinds, iterator->number, iterator->interval, iterator->hBitmap));
		}
	}
}

void ObjectManager::GetImageDataList(list<HBITMAP>* imageDataList)
{
	hbmpList = *imageDataList;
}

void ObjectManager::LoadCharacterData()
{
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
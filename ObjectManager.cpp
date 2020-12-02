#include "ObjectManager.h"
#include "Obj.h"
#include "StaticObject.h"
#include "Character.h"
#include <sstream>




void ObjectManager::Input()
{
	for (auto it = objectVector.begin(); it != objectVector.end(); it++)
		(*it)->Input();
}

void ObjectManager::Render(HDC hdc, HDC memDCBack, HDC memDC)
{
	for (auto it = objectVector.begin(); it != objectVector.end(); it++)
		(*it)->Render(memDCBack, memDC);
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
				
			objectVector.emplace_back(new StaticObject(iterator->name, { iterator->x,iterator->y }, { bitMap.bmWidth ,bitMap.bmHeight }, iterator->kinds, iterator->number, iterator->interval, iterator->hBitmap));
		}
	}
}

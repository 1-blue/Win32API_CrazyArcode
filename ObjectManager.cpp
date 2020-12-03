#include "ObjectManager.h"
#include "Obj.h"
#include "Character.h"
#include "WaitingUI.h"

ObjectManager::ObjectManager(int *stage)
{
	this->stage = stage;
}

ObjectManager::~ObjectManager()
{
	for (auto objs : defaultDataVector)
		delete objs;
	defaultDataVector.clear();
}

void ObjectManager::Input()
{
	if (*stage == GameStage::LOBBY)
	{
		for (auto it = defaultDataVector.begin(); it != defaultDataVector.end(); it++)
			(*it)->Input();
	}
	else if (*stage == GameStage::INGAME)
	{
		for (auto it = inGameSceneDataVector.begin(); it != inGameSceneDataVector.end(); it++)
			(*it)->Input();
	}
	
}

void ObjectManager::Update()
{
	if (*stage == GameStage::LOBBY)
	{
		for (auto it = defaultDataVector.begin(); it != defaultDataVector.end(); it++)
			(*it)->Update();
	}
	else if (*stage == GameStage::INGAME)
	{
		for (auto it = inGameSceneDataVector.begin(); it != inGameSceneDataVector.end(); it++)
			(*it)->Update();
	}
}

void ObjectManager::Render(HDC hdc, HDC memDCBack, HDC memDC)
{
	if (*stage == GameStage::LOBBY)
	{
		for (auto it = defaultDataVector.begin(); it != defaultDataVector.end(); it++)
			(*it)->Render(memDCBack, memDC);
	}
	else if (*stage == GameStage::INGAME)
	{
		for (auto it = inGameSceneDataVector.begin(); it != inGameSceneDataVector.end(); it++)
			(*it)->Render(memDCBack, memDC);
	}
}

void ObjectManager::LoadDefaultData(const vector<pImageData>& bitmapVector)
{
	BITMAP bitMap;
	this->bitmapVector = bitmapVector;

	for (auto iterator : bitmapVector)
	{
		if (iterator->objType == 0)
		{
			GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);

			defaultDataVector.emplace_back(new WaitingUI(iterator->name, { iterator->x,iterator->y }, { bitMap.bmWidth ,bitMap.bmHeight }, iterator->kinds, iterator->number, iterator->interval, iterator->hBitmap));
		}
	}
}

void ObjectManager::LoadInGameImageData(const vector<pImageData>& bitmapVector)
{
	BITMAP bitMap;

	for (auto iterator : bitmapVector)
	{
		GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);
		if (iterator->objType == 0)
			inGameSceneDataVector.emplace_back(new StaticObject(iterator->name, { iterator->x,iterator->y }, { bitMap.bmWidth ,bitMap.bmHeight }, iterator->hBitmap));
		else 
			inGameSceneDataVector.emplace_back(new DynamicObject(iterator->name, { iterator->x,iterator->y }, { bitMap.bmWidth ,bitMap.bmHeight }, iterator->kinds, iterator->number, iterator->interval, iterator->hBitmap));
	}
}

void ObjectManager::GetImageDataList(list<HBITMAP>* imageDataList)
{
	hbmpList = *imageDataList;
}

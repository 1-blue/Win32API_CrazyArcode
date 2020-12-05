#include "ObjectManager.h"
#include "Obj.h"
#include "Character.h"
#include "StaticObject.h"

//추가
#include "Blank.h"
#include "Block.h"
#include "Wall.h"

ObjectManager::ObjectManager(int *stage)
{
	this->stage = stage;
}

ObjectManager::~ObjectManager()
{
	for (auto objs : inGameSceneDataVector)
		delete objs;
	inGameSceneDataVector.clear();

	for (auto objs : CharacterDataVector)
		delete objs;
	CharacterDataVector.clear();
}

void ObjectManager::Input()
{
	for (auto it = inGameSceneDataVector.begin(); it != inGameSceneDataVector.end(); it++)
		(*it)->Input();

	for (const auto& character : CharacterDataVector)
		character->Input();
}

void ObjectManager::Update()
{
	for (auto it = inGameSceneDataVector.begin(); it != inGameSceneDataVector.end(); it++)
		(*it)->Update();

	for (const auto& character : CharacterDataVector)
		character->Update();
}

void ObjectManager::Render(HDC hdc, HDC memDCBack, HDC memDC)
{
	for (auto it = inGameSceneDataVector.begin(); it != inGameSceneDataVector.end(); it++)
		(*it)->Render(memDCBack, memDC);

	for (const auto& character : CharacterDataVector)
		character->Render(memDCBack, memDC);
}

void ObjectManager::LoadInGameImageData(const vector<pImageData>& bitmapVector)
{
	BITMAP bitMap;

	for (const auto iterator : bitmapVector)
	{
		GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);
		if (iterator->objType == 0)	//static
			inGameSceneDataVector.emplace_back(new StaticObject(iterator->name, { iterator->x,iterator->y }, { bitMap.bmWidth ,bitMap.bmHeight }, iterator->hBitmap));
		else						//dynamic
			inGameSceneDataVector.emplace_back(new DynamicObject(iterator->name, { iterator->x,iterator->y }, { bitMap.bmWidth ,bitMap.bmHeight },  iterator->hNumber, iterator->vNumber, iterator->hBitmap));
	}
}

void ObjectManager::LoadRedCharacterImageData(pImageData characterImage)
{
	BITMAP bitMap;
	GetObject(characterImage->hBitmap, sizeof(BITMAP), &bitMap);

	CharacterDataVector.emplace_back(new Character(characterImage->name,
		{ characterImage->x,characterImage->y },
		{ bitMap.bmWidth ,bitMap.bmHeight },
		characterImage->hNumber, characterImage->vNumber,
		bitMap.bmWidth / characterImage->vNumber, bitMap.bmHeight / characterImage->hNumber,
		characterImage->hBitmap));
}

void ObjectManager::LoadBlueCharacterImageData(pImageData characterImage)
{
	BITMAP bitMap;
	GetObject(characterImage->hBitmap, sizeof(BITMAP), &bitMap);

	CharacterDataVector.emplace_back( new Character(characterImage->name,
		{ characterImage->x,characterImage->y },
		{ bitMap.bmWidth ,bitMap.bmHeight },
		characterImage->hNumber, characterImage->vNumber,
		bitMap.bmWidth / characterImage->vNumber, bitMap.bmHeight / characterImage->hNumber,
		characterImage->hBitmap));
}

void ObjectManager::LoadRedCharacterStatsData(CharacterStatsData characterStats)
{
	dynamic_cast<Character*>(CharacterDataVector[0])->SetStats(characterStats);
}

void ObjectManager::LoadBlueCharacterStatsData(CharacterStatsData characterStats)
{
	dynamic_cast<Character*>(CharacterDataVector[1])->SetStats(characterStats);
}

void ObjectManager::LoadStaticObjectData(const MapData& mapData)
{
	//나중에 생성자로 각종 정보들 넘겨주기

	for (int h = 0; h < 13; h++)		//일단 맵세로길이
	{
		for (int w = 0; w < 15; w++)	//맵가로길이
		{
			switch (mapData.data[h][w])
			{
			case Objects::BLANK:
				//공백생성
				mapObjectVector.emplace_back(new Blank());
				break;
			case Objects::BLOCK:
				//블록생성
				mapObjectVector.emplace_back(new Block());
				break;
			case Objects::WALL:
				//벽생성
				mapObjectVector.emplace_back(new Wall());
				break;
			}
		}
	}
	int x = 10;
}

#include "InGameScene.h"
#include "Character.h"
#include "WaterBallon.h"
#include "Block.h"
#include "Wall.h"

InGameScene::~InGameScene()
{
	for (auto& obj : inGameObjectVector)
		delete obj;
	inGameObjectVector.clear();

	for (auto& character : characterList)
		delete character;
	characterList.clear();

	for (auto& wb : waterBallon)
		delete wb;
	waterBallon.clear();

	objectsData.clear();
	objectsBitmap.clear();
}

void InGameScene::Process(HDC memDCBack, HDC memDC)
{
	for (const auto& inGameObj : inGameObjectVector)
	{
		inGameObj->Input();
		inGameObj->Update();
		inGameObj->Render(memDCBack, memDC);
	}

	for (const auto& waterBallons : waterBallon)
	{
		waterBallons->Input();
		waterBallons->Update();
		waterBallons->Render(memDCBack, memDC);
	}

	for (const auto& character : characterList)
	{
		character->Input();
		character->Update();
		this->CreateWaterBallon(character);
		character->ImmovableArea(inGameObjectVector);	//이동제한체크.. 물풍선으로 블럭파괴될경우 데이터 최신화해줘야함
		character->Render(memDCBack, memDC);
	}
}

void InGameScene::LoadData(const vector<pImageData>& inGameData)
{
	this->LoadInGameImage(inGameData);
}

void InGameScene::LoadInGameImage(const vector<pImageData>& inGameBackGround)
{
	BITMAP bitMap;

	for (const auto& iterator : inGameBackGround)
	{
		GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);

		if(iterator->name == "background")
		{
			inGameObjectVector.emplace_back(new StaticObject(iterator->name,
				{ iterator->x,iterator->y },
				{ bitMap.bmWidth ,bitMap.bmHeight },
				iterator->hBitmap));
		}
		else		//block, wall, waterBallon순서대로 들어감
		{
			GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);
			objectsData.emplace_back(iterator);
			objectsBitmap.emplace_back(bitMap);
		}
	}
}

void InGameScene::LoadCharacterData(const pImageData characterImage, CharacterStatsData characterStats)
{
	BITMAP bitMap;

	GetObject(characterImage->hBitmap, sizeof(BITMAP), &bitMap);
	characterList.emplace_back(new Character(
		characterImage->name,
		{ characterImage->x,characterImage->y },
		{ bitMap.bmWidth ,bitMap.bmHeight },
		characterImage->hNumber, characterImage->vNumber,
		characterImage->hBitmap,
		characterStats));
}

void InGameScene::LoadStaticObjectData(const MapData& mapData)
{
	for (int h = 0; h < 11; h++)		//일단 맵세로길이
	{
		for (int w = 0; w < 15; w++)	//맵가로길이
		{
			switch (mapData.data[h][w])
			{
			case Objects::BLOCK:
				//블록생성
				inGameObjectVector.emplace_back(new Block(
					objectsData[0]->name,
					{ objectsData[0]->x + objectsBitmap[0].bmWidth * w, objectsData[0]->y + objectsBitmap[0].bmHeight * h },
					{ objectsBitmap[0].bmWidth, objectsBitmap[0].bmHeight },
					objectsData[0]->hBitmap
					));
				break;
			case Objects::WALL:		//벽생성.. 벽이랑 블럭이랑 사이즈가 달라가지고 놓는 위치 지정할때 블럭사이즈이용하고, -20함
				inGameObjectVector.emplace_back(new Wall(
					objectsData[1]->name,
					{ objectsData[1]->x + objectsBitmap[0].bmWidth * w, objectsData[1]->y + objectsBitmap[0].bmHeight * h - SIZE_TUNING},
					{ objectsBitmap[1].bmWidth, objectsBitmap[1].bmHeight },
					objectsData[1]->hBitmap
				));
				break;
			}
		}
	}
}

void InGameScene::CreateWaterBallon(Character* character)
{
	Attack& attack = character->GetAttack();

	if (attack.isAttack)		//물풍선생성
	{
		attack.isAttack = false;
		waterBallon.emplace_back(new WaterBallon(
			objectsData[2]->name,
			{ attack.pos.x,attack.pos.y },
			{ objectsBitmap[2].bmWidth,objectsBitmap[2].bmHeight },
			objectsData[2]->hNumber, objectsData[2]->vNumber,
			objectsData[2]->hBitmap
		));
		//물풍선위치를 캐릭터에 전송
		waterBallonPos.emplace_back(ObjectData::Position{ attack.pos.x, attack.pos.y });
		character->GetWaterBallonList(waterBallonPos);
	}
}


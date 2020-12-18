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
	allInGameScene.clear();
}

void InGameScene::Process(HDC memDCBack, HDC memDC)
{
	for (const auto& inGameObj : inGameObjectVector)
	{
		inGameObj->Input();
		inGameObj->Update();
	}

	for (const auto& waterBallons : waterBallon)
	{
		waterBallons->Input();
		waterBallons->Update();
	}

	for (const auto& character : characterList)
	{
		character->Input();
		this->CreateWaterBallon(character);
		character->Update();
		character->LateUpdate(inGameObjectVector);
	}

	//우선순위에 맞게 정렬후 출력.. 물풍선이랑 캐릭터 적용을 못함..
	allInGameScene.sort(SortObject);
	for (const auto& ts : allInGameScene)
	{
		ts->Render(memDCBack, memDC);
	}

	MessageQueue::RunEventQueue(inGameObjectVector);
}

void InGameScene::LoadData(const vector<pImageData>& inGameData)
{
	this->LoadInGameImage(inGameData);
}

void InGameScene::LoadInGameImage(const vector<pImageData>& inGameBackGround)
{
	BITMAP bitMap;

	for (const auto& inGameObj : inGameBackGround)
	{
		GetObject(inGameObj->hBitmap, sizeof(BITMAP), &bitMap);

		switch (inGameObj->objType)
		{
		case 0:					//static
			inGameObjectVector.emplace_back(new StaticObject(inGameObj->name,
				{ inGameObj->x,inGameObj->y },
				{ bitMap.bmWidth ,bitMap.bmHeight },
				inGameObj->hBitmap));
			allInGameScene.emplace_back(inGameObjectVector.back());
			break;
		case 1:					//dynamic
			inGameObjectVector.emplace_back(new DynamicObject(inGameObj->name,
				{ inGameObj->x,inGameObj->y },
				{ bitMap.bmWidth ,bitMap.bmHeight },
				inGameObj->hNumber, inGameObj->vNumber,
				inGameObj->hBitmap));
			break;
		case 2:					//button
			inGameObjectVector.emplace_back(new BtnObj(inGameObj->name,
				{ inGameObj->x,inGameObj->y },
				{ bitMap.bmWidth ,bitMap.bmHeight },
				inGameObj->hNumber, inGameObj->vNumber,
				inGameObj->hBitmap));
			break;
		default:				//기타, 물풍선,벽,블록
			GetObject(inGameObj->hBitmap, sizeof(BITMAP), &bitMap);
			objectsData.emplace_back(inGameObj);
			objectsBitmap.emplace_back(bitMap);
			break;
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

	allInGameScene.emplace_back(characterList.back());
}

void InGameScene::LoadStaticObjectData(const MapData& mapData)
{
	for (int h = 0; h < 11; h++)		//일단 맵세로길이
	{
		for (int w = 0; w < 15; w++)	//맵가로길이
		{
			switch (mapData.data[h][w])
			{
			case Objects::BLOCK:		//블록생성
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
			allInGameScene.emplace_back(inGameObjectVector.back());
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
		allInGameScene.emplace_back(waterBallon.back());
	}
}

bool InGameScene::SortObject(Obj* obj1, Obj* obj2)
{
	return obj1->GetOrder() < obj2->GetOrder();
}
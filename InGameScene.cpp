#include "InGameScene.h"
#include "InGameBackGround.h"
#include "Character.h"
#include "WaterBallon.h"
#include "Blank.h"
#include "Block.h"
#include "Wall.h"

void InGameScene::Process(HDC memDCBack, HDC memDC)
{
	for (const auto& inGame : inGameObjectVector)
	{
		inGame->Input();
		inGame->Update();
		inGame->Render(memDCBack, memDC);
	}

	Attack attack{ false, -1, 0, 0 };	//캐릭터공격
	for (const auto& character : characterList)
	{
		character->Input();
		character->Update();
		character->Render(memDCBack, memDC);

		attack = dynamic_cast<Character*>(character)->GetAttack();
		
		if (attack.isAttack)		//물풍선생성
		{
			attack.isAttack = false;
			waterBallon.emplace_back(new WaterBallon(waterBallonData->name,
				{ attack.pos.x,attack.pos.y },
				{ waterBallonBitmap.bmWidth,waterBallonBitmap.bmHeight},
				waterBallonData->hNumber, waterBallonData->vNumber,
				waterBallonData->hBitmap
			));
		}
	}

	for (const auto& inGame : waterBallon)
	{
		inGame->Input();
		inGame->Update();
		inGame->Render(memDCBack, memDC);
	}
}

void InGameScene::LoadData(const vector<pImageData>& inGameData)
{
	this->LoadBackGroundImage(inGameData);
}

void InGameScene::LoadBackGroundImage(const vector<pImageData>& inGameData)
{
	BITMAP bitMap;

	for (const auto& iterator : inGameData)
	{
		GetObject(iterator->hBitmap, sizeof(BITMAP), &bitMap);
		inGameObjectVector.emplace_back(new StaticObject(iterator->name,
			{ iterator->x,iterator->y },
			{ bitMap.bmWidth ,bitMap.bmHeight },
			iterator->hBitmap));
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
	//나중에 생성자로 각종 정보들 넘겨주기
	for (int h = 0; h < 13; h++)		//일단 맵세로길이
	{
		for (int w = 0; w < 15; w++)	//맵가로길이
		{
			switch (mapData.data[h][w])
			{
			case Objects::BLANK:
				//공백생성
				inGameObjectVector.emplace_back(new Blank());
				break;
			case Objects::BLOCK:
				//블록생성
				inGameObjectVector.emplace_back(new Block());
				break;
			case Objects::WALL:
				//벽생성
				inGameObjectVector.emplace_back(new Wall());
				break;
			}
		}
	}
}

void InGameScene::LoadWaterBallon(const pImageData waterBallon)
{
	this->waterBallonData = waterBallon;
	GetObject(waterBallonData->hBitmap, sizeof(BITMAP), &waterBallonBitmap);
}
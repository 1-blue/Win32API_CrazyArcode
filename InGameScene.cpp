#include "InGameScene.h"
#include "Character.h"
#include "WaterBallon.h"
#include "Block.h"
#include "Wall.h"

ObjectData::POSITION InGameScene::removeWaterBallonPos{ 0,0 };

void InGameScene::Init()
{
	for (auto& scene : allInGameScene)		//여기서 사용하던 모든 오브젝트들 delete
		delete scene;

	//list들 clear
	allInGameScene.clear();		
	inGameObjectList.clear();
	characterList.clear();
	waterBallon.clear();
	waterBallonPos.clear();
}

InGameScene::~InGameScene()
{
	for (auto& scene : allInGameScene)		//여기서 사용하던 모든 오브젝트들 delete
		delete scene;

	//data와 bitmap가진 list까지 모두 clear
	allInGameScene.clear();
	inGameObjectList.clear();
	characterList.clear();
	waterBallon.clear();
	objectsData.clear();
	objectsBitmap.clear();
	allInGameScene.clear();
}

void InGameScene::Process(HDC memDCBack, HDC memDC)
{
	for (const auto& inGameObj : inGameObjectList)
	{
		inGameObj->Input();
		inGameObj->Update();
	}


	for (const auto& waterBallons : waterBallon)
	{
		waterBallons->Input();
		waterBallons->Update();

		if (waterBallons->GetIsEffect())
			DeleteHitObject(waterBallons->GetHitObjectPos());

		if (!waterBallons->GetIsAlive())
			isDeleteWaterBallon = true;
	}

	if(isDeleteWaterBallon)
		DeleteWaterBallons();

	for (const auto& character : characterList)
	{
		character->Input();
		this->CreateWaterBallon(character);
		character->Update();
		character->LateUpdate(inGameObjectList);
	}


	//우선순위에 맞게 정렬후 출력.. 물풍선이랑 캐릭터 적용을 못함..
	allInGameScene.sort(SortObject);
	for (const auto& ts : allInGameScene)
		ts->Render(memDCBack, memDC);
}

void InGameScene::LoadData(const vector<pImageData>& inGameData)
{
	this->LoadInGameImage(inGameData);
}

list<Obj*>& InGameScene::GetInGameObjList()
{
	return inGameObjectList;
}

void InGameScene::GetMapData(MapData mapData)
{
	this->mapData = mapData;
}

void InGameScene::LoadInGameImage(const vector<pImageData>& inGameBackGround)
{
	BITMAP bitMap;

	for (const auto& inGameObj : inGameBackGround)
	{
		GetObject(inGameObj->hBitmap, sizeof(BITMAP), &bitMap);

		switch (inGameObj->objType)
		{
		case Objects::STATIC:					//static
			inGameObjectList.emplace_back(new StaticObject(inGameObj->name,
				{ inGameObj->x,inGameObj->y },
				{ bitMap.bmWidth ,bitMap.bmHeight },
				inGameObj->hBitmap));
			allInGameScene.emplace_back(inGameObjectList.back());		//allInGameScene에 백그라운드
			break;
		case Objects::DYNAMIC:					//dynamic
			inGameObjectList.emplace_back(new DynamicObject(inGameObj->name,
				{ inGameObj->x,inGameObj->y },
				{ bitMap.bmWidth ,bitMap.bmHeight },
				inGameObj->hNumber, inGameObj->vNumber,
				inGameObj->hBitmap));
			break;
		case Objects::BUTTON:					//button
			inGameObjectList.emplace_back(new BtnObj(inGameObj->name,
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

void InGameScene::LoadCharacterData(const pImageData characterImage, const pImageData trappedImage, const pImageData dieImage, CharacterStatsData characterStats)
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

	//die, trapped추가
	characterList.back()->GetDefaultImage(trappedImage, dieImage);
}

void InGameScene::LoadStaticObjectData()
{
	for (int h = 0; h < MAP_HEIGHT_SIZE; h++)		//일단 맵세로길이
	{
		for (int w = 0; w < MAP_WIDTH_SIZE; w++)	//맵가로길이
		{
			switch (mapData.data[h][w])
			{
			case Objects::BLOCK:
				//블록생성
				inGameObjectList.emplace_back(new Block(
					objectsData[0]->name,
					{ objectsData[0]->x + objectsBitmap[0].bmWidth * w, objectsData[0]->y + objectsBitmap[0].bmHeight * h },
					{ objectsBitmap[0].bmWidth, objectsBitmap[0].bmHeight },
					objectsData[0]->hBitmap
					));
				allInGameScene.emplace_back(inGameObjectList.back());
				break;
			case Objects::WALL:		//벽생성.. 벽이랑 블럭이랑 사이즈가 달라가지고 놓는 위치 지정할때 블럭사이즈이용하고, -20함
				inGameObjectList.emplace_back(new Wall(
					objectsData[1]->name,
					{ objectsData[1]->x + objectsBitmap[0].bmWidth * w, objectsData[1]->y + objectsBitmap[0].bmHeight * h - SIZE_TUNING},
					{ objectsBitmap[1].bmWidth, objectsBitmap[1].bmHeight },
					objectsData[1]->hBitmap
				));
				allInGameScene.emplace_back(inGameObjectList.back());
				break;
			}
		}
	}
}

void InGameScene::DeleteHitObject(const ObjectData::POSITION* hitObjectPos)
{
	bool isDeleteBlocks = false;
	bool isDeleteWaterBallons = false;
	list <int> hitObjectIndex;

	//북동남서, (크기 4)
	for (int i = 0; i < 4; i++)
	{
		if (hitObjectPos[i].x == -1)
			continue;
		if (hitObjectPos[i].y == -1)
			continue;

		switch (mapData.data[hitObjectPos[i].y][hitObjectPos[i].x])
		{
		case 1:		// 블럭
			isDeleteBlocks = true;
			hitObjectIndex.emplace_back(i);
			mapData.data[hitObjectPos[i].y][hitObjectPos[i].x] = 0;		//맵에서 오브젝트 삭제
			break;
		case 3:		//물풍선
			isDeleteWaterBallons = true;
			hitObjectIndex.emplace_back(i);
			mapData.data[hitObjectPos[i].y][hitObjectPos[i].x] = 0;		//맵에서 오브젝트 삭제
			break;
		}
	}

	//물풍선 삭제 처리
	if (isDeleteWaterBallons)
	{

		//삭제부분
		for (auto waterBallons : waterBallon)
		{
			for (auto hitObjects : hitObjectIndex)
			{
				if (waterBallons->GetMapPos() == hitObjectPos[hitObjects])
					waterBallons->SetIsEffect(true);
			}
		}
	}

	if (!isDeleteBlocks)
		return;
	//블럭 삭제 부분
	for (auto blocks = inGameObjectList.begin(); blocks != inGameObjectList.end();)
	{
		for (auto hitObjects : hitObjectIndex)
		{
			//맵좌표의 블럭을 찾아서 삭제!
			if ((*blocks)->GetPosition().x == hitObjectPos[hitObjects].x && (*blocks)->GetPosition().y == hitObjectPos[hitObjects].y)
			{
				*blocks = nullptr;
				delete* blocks;
				inGameObjectList.erase(blocks);
			}
			else
				blocks++;
		}
	}

	//모든 오브젝트 저장 변수에서 해당 오브젝트까지 삭제
	for (auto allInGameObjects = allInGameScene.begin(); allInGameObjects != allInGameScene.end();)
	{
		if (*allInGameObjects == nullptr)
			allInGameScene.erase(allInGameObjects);
		else
			allInGameObjects++;
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
			objectsData[2]->hBitmap,
			character->GetWaterBallonBLength()
		));
		waterBallon.back()->SetColor(attack.isColor);

		//풍선에 맵정보 제공
		waterBallon.back()->GetMapData(&mapData);

		//물풍선위치를 캐릭터에 전송
		waterBallonPos.emplace_back(ObjectData::Position{ attack.pos.x, attack.pos.y });
		for (const auto& c : characterList)
			c->SetWaterBallonList(waterBallonPos);

		allInGameScene.emplace_back(waterBallon.back());
	}
}

void InGameScene::DeleteWaterBallons()
{
	for (auto iterator = waterBallon.begin(); iterator != waterBallon.end();)
	{
		if (!(*iterator)->GetIsAlive())
		{
			switch ((*iterator)->GetColor())
			{
			case CharacterColor::RED:
				for (const auto& c : characterList)
					c->SettingBallonNumber(CharacterColor::RED);
				break;
			case CharacterColor::BLUE:
				for (const auto& c : characterList)
					c->SettingBallonNumber(CharacterColor::BLUE);
				break;
			}

			removeWaterBallonPos = (*iterator)->GetPosition();	//삭제할 물풍선 좌표 받아서 저장
			allInGameScene.remove_if(RemoveWaterBallonData);	//allInGameScene에서 물풍선데이터삭제
			delete* iterator;
			waterBallon.erase(iterator++);
		}
		else
			iterator++;
	}

	isDeleteWaterBallon = false;

	waterBallonPos.remove_if(RemoveWaterBallonData1);	//waterBallonPos에서 물풍선데이터삭제
	for (const auto& c : characterList)	
		c->SetWaterBallonList(waterBallonPos);			//캐릭터들한테 물풍선 위치값 최신화
}

bool InGameScene::SortObject(Obj* obj1, Obj* obj2)
{
	return obj1->GetOrder() < obj2->GetOrder();
}

bool InGameScene::RemoveWaterBallonData(Obj* tempWaterBallon)
{
	//if (tempWaterBallon->GetPosition() == removeWaterBallonPos)		//이거 하나는 const고 하나는 const아니라서 직접비교함
	if (tempWaterBallon->GetPosition().x == removeWaterBallonPos.x && tempWaterBallon->GetPosition().y == removeWaterBallonPos.y)
		return true;
	return false;
}

bool InGameScene::RemoveWaterBallonData1(ObjectData::POSITION tempWaterBallon)
{
	if (tempWaterBallon == removeWaterBallonPos && tempWaterBallon == removeWaterBallonPos)
		return true;
	return false;
}

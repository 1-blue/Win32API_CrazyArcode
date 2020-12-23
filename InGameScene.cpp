#include "InGameScene.h"
#include "Character.h"
#include "WaterBallon.h"
#include "Block.h"
#include "Wall.h"
#include "Item.h"

ObjectData::POSITION InGameScene::removeWaterBallonPos{ 0,0 };
ObjectData::POSITION InGameScene::removeItemPos{ -1,-1 };

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

	isEndGame = false;
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
	for (auto inGameObj : inGameObjectList)
	{
		inGameObj->Input();
		inGameObj->Update();
	}

	for (const auto& waterBallons : waterBallon)
	{
		waterBallons->Update();

		if (WaterBallonState::EXPLOSION == waterBallons->GetState())
		{
			DeleteHitObject(waterBallons->GetHitObjectPos());
			for (const auto& character : characterList)		//물풍선 터질때 공격범위 전송
			{
				character->SetAttackArea(waterBallons->GetAttackArea());
				this->CheckWaterBallonItem(waterBallons->GetAttackArea());
			}
		}	
	}

	//위에서 설정한 값으로 물풍선 삭제처리
	DeleteWaterBallons();

	for (const auto& character : characterList)
	{
		character->Input();
		this->CreateWaterBallon(character);
		character->Update();
		character->LateUpdate(inGameObjectList);
		characterList.front()->CheckTrappedCollision(character);
	}

	CheckCharacterItem();

	//우선순위에 맞게 정렬후 출력.. 물풍선이랑 캐릭터 적용을 못함..
	allInGameScene.sort(SortObject);
	for (const auto& ts : allInGameScene)
		ts->Render(memDCBack, memDC);

	if (isEndGame)
	{
		if(GetTickCount64() > endGameTime + 2000)
			MessageQueue::AddEventQueue({ EnumObj::exit, false });

		return;
	}

	//1명이 죽었을 때 게임오버 처리
	for (const auto& character : characterList)
	{
		if (character->GetState() == State::DEAD)
			GameOver(character->GetColor());
	}

	//제한시간 3분 경과 시 DRAW 처리
	if(GetTickCount64() > inGamePlayTime + 180000)
		GameOver(-1);
}

void InGameScene::LoadData(const vector<pImageData>& inGameData)
{
	this->LoadInGameImage(inGameData);
}

void InGameScene::InitInGamePlayTime()
{
	inGamePlayTime = GetTickCount64();
}

list<Obj*>& InGameScene::GetInGameObjList()
{
	return inGameObjectList;
}

void InGameScene::GetMapData(MapData mapData)
{
	this->mapData = mapData;
}

void InGameScene::LoadInGameImage(const vector<pImageData>& inGameImage)
{
	BITMAP bitMap;

	for (const auto& inGameObj : inGameImage)
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

void InGameScene::LoadItemImage(const pImageData itemImage)
{
	this->itemData = itemImage;										//아이템관련 데이터 변수에 저장
	GetObject(itemData->hBitmap, sizeof(BITMAP), &itemBitmap);		//아이템 비트맵정보 저장
}

void InGameScene::LoadStaticObjectData()
{
	for (int h = 0; h < MAP_HEIGHT_SIZE; h++)		//맵세로길이
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

void InGameScene::DeleteHitObject(vector<ObjectData::POSITION> hitObjectPos)
{
	bool isDeleteBlocks = false;
	bool isDeleteWaterBallons = false;
	static int ramdomNumber = 0;

	for (auto hitObjects : hitObjectPos)
	{
		switch (mapData.data[hitObjects.y][hitObjects.x])
		{
		case 1:		// 블럭
			isDeleteBlocks = true;
			mapData.data[hitObjects.y][hitObjects.x] = 0;		//맵에서 오브젝트 삭제
			continue;
		case 3:		//물풍선
			isDeleteWaterBallons = true;
			mapData.data[hitObjects.y][hitObjects.x] = 0;		//맵에서 오브젝트 삭제
			continue;
		}
	}

	//물풍선 삭제 처리
	if (isDeleteWaterBallons)
	{
		//삭제부분
		for (auto waterBallons : waterBallon)
		{
			for (auto hitObjects : hitObjectPos)
			{
				if (waterBallons->GetMapPos() == hitObjects)
					waterBallons->SetIExplosionState();
			}
		}
	}

	if (!isDeleteBlocks)
		return;

	ObjectData::POSITION mapPos{ 0 };

	for (auto hitObjects : hitObjectPos)
	{
		for (auto blocks = inGameObjectList.begin(); blocks != inGameObjectList.end();)
		{
			//오브젝트 좌표값을 맵의 좌표값으로 변환
			mapPos.x = (((*blocks)->GetPosition().x + 20) / BLOCK_X) - 1;
			mapPos.y = (((*blocks)->GetPosition().y + 2) / BLOCK_Y) - 1;


			if ((mapPos.x == hitObjects.x) && (mapPos.y == hitObjects.y))
			{	//allInGameScene에 있는 값 먼저 삭제하고
				allInGameScene.remove_if([=](Obj* tempWaterBallon)->bool {
					return ((tempWaterBallon->GetPosition().x == (*blocks)->GetPosition().x) && (tempWaterBallon->GetPosition().y == (*blocks)->GetPosition().y));
					});

				//블럭 삭제할때 그좌표에 아이템생성
				srand((unsigned int)time(NULL));
				++ramdomNumber;
				if ((rand() * ramdomNumber + ramdomNumber) % 3 == 0)
				{
					inGameObjectList.emplace_back(new Item(
						itemData->name,
						(*blocks)->GetPosition(),
						{ itemBitmap.bmWidth, itemBitmap.bmHeight },
						itemData->hNumber, itemData->vNumber,
						itemData->hBitmap,
						ramdomNumber
					));
					allInGameScene.emplace_back(inGameObjectList.back());
					itemPos.emplace_back(ItemData{ inGameObjectList.back()->GetName(), (*blocks)->GetPosition() });
				}

				//inGameObjectList의 블럭 삭제
				delete* blocks;
				inGameObjectList.erase(blocks++);
				break;
			}
			else
				++blocks;
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
			objectsData[2]->hBitmap,
			character->GetWaterBallonLength()
		));
		waterBallon.back()->SetColor(attack.isColor);

		//풍선에 맵정보 제공
		waterBallon.back()->GetMapData(&mapData);

		//물풍선위치를 캐릭터에 전송
		waterBallonPos.emplace_back(ObjectData::Position{ attack.pos.x, attack.pos.y });
		for (const auto& c : characterList)
			c->SetWaterBallonPos(waterBallonPos);

		allInGameScene.emplace_back(waterBallon.back());
	}
}

void InGameScene::DeleteWaterBallons()
{
	for (auto iterator = waterBallon.begin(); iterator != waterBallon.end();)
	{
		if (WaterBallonState::DIE == (*iterator)->GetState())
		{
			switch ((*iterator)->GetColor())
			{
			case CharacterColor::RED:
				for (const auto& c : characterList)
				{
					if(c->GetColor() == CharacterColor::RED)
						c->SettingBallonNumber();
				}
					
				break;
			case CharacterColor::BLUE:
				for (const auto& c : characterList)
				{
					if (c->GetColor() == CharacterColor::BLUE)
						c->SettingBallonNumber();
				}
				break;
			}

			removeWaterBallonPos = (*iterator)->GetPosition();	//삭제할 물풍선 좌표 받아서 저장
			allInGameScene.remove_if(RemoveWaterBallonData);	//allInGameScene에서 물풍선데이터삭제
			waterBallonPos.remove_if(RemoveWaterBallonData1);	//waterBallonPos에서 물풍선데이터삭제
			delete* iterator;
			waterBallon.erase(iterator++);
		}
		else
			iterator++;
	}

	for (const auto& c : characterList)	
		c->SetWaterBallonPos(waterBallonPos);			//캐릭터들한테 물풍선 위치값 최신화
}

void InGameScene::CheckCharacterItem()
{
	RECT temp;
	for (const auto& character : characterList)
	{
		if (character->GetState() != State::NORMAL)
			return;

		RECT characterRect{ character->GetPosition().x, character->GetPosition().y, character->GetPosition().x + BLOCK_X, character->GetPosition().y + BLOCK_Y };
		for (const auto& item : itemPos)
		{
			RECT itemRect{ item.pos.x + 10, item.pos.y + 10, item.pos.x + BLOCK_X - 10, item.pos.y + BLOCK_Y - 10 };
			if (IntersectRect(&temp, &characterRect, &itemRect))
			{
				if (item.name == MessageQueue::StringToEnum("BompUP"))
					character->WaterBallonNumberUP();
				else if (item.name == MessageQueue::StringToEnum("PowerUP"))
					character->WaterBallonLengthUP();
				else if (item.name == MessageQueue::StringToEnum("SpeedUP"))
					character->SpeedUP();
				removeItemPos = item.pos;
			}
		}
	}

	if (removeItemPos.x != -1)
	{
		allInGameScene.remove_if(RemoveItemData);	//allInGameScene에서 아이템삭제
		itemPos.remove_if(RemoveItemData1);			//item포지션리스트에서 아이템삭제
		removeItemPos.x = -1;
	}
}

void InGameScene::CheckWaterBallonItem(const AttackArea& attackArea)
{
	POINT boomPosition{ -1, -1 };	//터지는 물풍선의 위치
	POINT boomPoint{ -1, -1 };		//터지는 물줄기와 아이템 조건검사할 좌표

	for (const auto& item : itemPos)
	{
		if (attackArea.pos.x != -1)
		{
			boomPosition.x = attackArea.pos.x * BLOCK_X + 20;
			boomPosition.y = attackArea.pos.y * BLOCK_Y + 25;

			//위
			for (int i = 0; i <= attackArea.t; i++)
			{
				boomPoint.y = boomPosition.y - (i * BLOCK_Y) + (BLOCK_Y / 2);
				boomPoint.x = boomPosition.x + (BLOCK_X / 2);
				if (item.pos.y <= boomPoint.y && item.pos.y + BLOCK_Y >= boomPoint.y
					&& item.pos.x <= boomPoint.x && item.pos.x + BLOCK_X >= boomPoint.x)
				{
					removeItemPos = item.pos;
				}
			}
			//우측
			for (int i = 0; i <= attackArea.r; i++)
			{
				boomPoint.y = boomPosition.y + (BLOCK_Y / 2);
				boomPoint.x = boomPosition.x + (i * BLOCK_X) + (BLOCK_X / 2);
				if (item.pos.y <= boomPoint.y && item.pos.y + BLOCK_Y >= boomPoint.y
					&& item.pos.x <= boomPoint.x && item.pos.x + BLOCK_X >= boomPoint.x)
				{
					removeItemPos = item.pos;
				}
			}
			//아래
			for (int i = 0; i <= attackArea.b; i++)
			{
				boomPoint.y = boomPosition.y + (i * BLOCK_Y) + (BLOCK_Y / 2);
				boomPoint.x = boomPosition.x + (BLOCK_X / 2);
				if (item.pos.y <= boomPoint.y && item.pos.y + BLOCK_Y >= boomPoint.y
					&& item.pos.x <= boomPoint.x && item.pos.x + BLOCK_X >= boomPoint.x)
				{
					removeItemPos = item.pos;
				}
			}
			//좌측
			for (int i = 0; i <= attackArea.l; i++)
			{
				boomPoint.y = boomPosition.y + (BLOCK_Y / 2);
				boomPoint.x = boomPosition.x - (i * BLOCK_X) + (BLOCK_X / 2);
				if (item.pos.y <= boomPoint.y && item.pos.y + BLOCK_Y >= boomPoint.y
					&& item.pos.x <= boomPoint.x && item.pos.x + BLOCK_X >= boomPoint.x)
				{
					removeItemPos = item.pos;
				}
			}
		}
	}

	if (removeItemPos.x != -1)
	{
		allInGameScene.remove_if(RemoveItemData);	//allInGameScene에서 아이템삭제
		itemPos.remove_if(RemoveItemData1);			//item포지션리스트에서 아이템삭제
		removeItemPos.x = -1;
	}
}

bool InGameScene::SortObject(Obj* obj1, Obj* obj2)
{
	return obj1->GetOrder() < obj2->GetOrder();
}

bool InGameScene::RemoveWaterBallonData(Obj* tempWaterBallon)
{
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

void InGameScene::GameOver(const int playerColor)
{
	ObjectData::POSITION winUIPos{0,0};
	ObjectData::POSITION loseUIPos{0,0};

	bool isDraw = false;

	switch (playerColor)
	{
	case CharacterColor::RED:
		winUIPos = { 20,100 };
		loseUIPos = { 300,100 };
		break;
	case CharacterColor::BLUE:
		winUIPos = { 370,100 };
		loseUIPos = { 15,100 };
		break;
	default:
		winUIPos = { 170,100 };
		isDraw = true;
		break;
	}
	
	if (isDraw)	//draw일 경우
	{
		for (auto inGameObjects : inGameObjectList)
		{
			if (inGameObjects->GetName() == EnumObj::drawUI)
			{
				inGameObjects->SetPosition(winUIPos);
				inGameObjects->SetOrder(255);
			}
		}
		isEndGame = true;
		endGameTime = GetTickCount64();

		return;
	}

	//UI 위치와 출력순서 수정해서 화면에 출력
	for (auto inGameObjects : inGameObjectList)
	{
		switch (inGameObjects->GetName())
		{
		case EnumObj::winUI:
			inGameObjects->SetPosition(winUIPos);
			inGameObjects->SetOrder(255);
			break;
		case EnumObj::loseUI:
			inGameObjects->SetPosition(loseUIPos);
			inGameObjects->SetOrder(254);
			break;
		}
	}

	isEndGame = true;
	endGameTime = GetTickCount64();
}

bool InGameScene::RemoveItemData(Obj* itemPosition)
{
	if (removeItemPos == itemPosition->GetPosition())
		return true;
	return false;
}

bool InGameScene::RemoveItemData1(ItemData itemPosition)
{
	if (removeItemPos == itemPosition.pos)
		return true;
	return false;
}

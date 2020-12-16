#pragma once
#include "DynamicObject.h"

class Character : public DynamicObject
{
private:
	CharacterStatsData characterStats{ 0 };	//캐릭터의 정보.. 물풍선개수, 속도 등을 가지고있음
	int color{ -1 };				//플레이어 색깔
	int dir{ Diraction::TOP };		//플레이어 이동방향
	POINT printPos{ 0, 0 };			//여러개 이미지중에서 출력할 위치
	Attack attack{ false, -1, 0, 0 };

	int prevDir{ Diraction::TOP };
	ULONGLONG charAnimationTick = GetTickCount64();

	ObjectData::Position prevRedPos;
	ObjectData::Position prevBluePos;

public:
	Character(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap, CharacterStatsData characterStats);
	~Character();

	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);
	Attack& GetAttack();

	void Manual();
	bool CheckmDelay(const int delayTime);
	void ImmovableArea(const list<Obj*>& inGameObjectVector);	//이동불가영역판단

};


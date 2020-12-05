#pragma once
#include "DynamicObject.h"

class Character : public DynamicObject
{
private:
	CharacterStatsData characterStats{ 0 };	//캐릭터의 정보.. 물풍선개수, 속도 등을 가지고있음
	int color{ -1 };				//플레이어 색깔
	int dir{ Diraction::TOP };		//플레이어 이동방향
	POINT printPos{ 0, 0 };			//여러개 이미지중에서 출력할 위치

public:
	Character(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, int hInterval, int vInterval, HBITMAP hBitmap);
	~Character();

	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);

public:
	void SetStats(CharacterStatsData characterStats);		//스텟은 요걸로 받음

};


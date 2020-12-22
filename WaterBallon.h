#pragma once
#include "DynamicObject.h"

class WaterBallon : public DynamicObject
{
private:
	int waterLength { 1 };	//물줄기
	int color{ -1 };

	ULONGLONG charAnimationTick;
	ULONGLONG deadlineTick{ 0 };

	MapData* mapData{ nullptr };

	Direction::DirectionVar printDirCount{ 0,0,0,0 };
	ObjectData::POSITION hitObjectPos[4] = { {-1,-1},{-1,-1},{-1,-1},{-1,-1} };	//피격 오브젝트 위치 (북,동,남,서)

	ObjectData::POSITION mapPos{ 0 };

	AttackArea attackArea{ {-1,-1}, -1, -1, -1, -1 };	//공격범위에대한 정보

	bool isEffect{ false };
	bool isAlive{ true };

	//물줄기 길이 설정
	void SetEffectDir(const int x, const int y, const int dir, int& dirCount);	//폭발범위 설정
public:
	WaterBallon(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap,const int& waterLength);
	~WaterBallon();

	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);
	void  BoomRender(HDC hDC, HDC memDc, const int printBoomImgCount, const int direction);
	
	void GetMapData(MapData* mapData);

	const bool GetIsEffect();
	const bool GetIsAlive();

	void SetIsEffect(const bool isEffect);

	ObjectData::POSITION GetMapPos();
	ObjectData::POSITION* GetHitObjectPos();

	void SetColor(int color);
	const int& GetColor() const;

	const AttackArea& GetAttackArea() const;
private:
	bool CheckmDelay(const int delayTime, ULONGLONG& tick);

};



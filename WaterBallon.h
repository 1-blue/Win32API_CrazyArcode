#pragma once
#include "DynamicObject.h"

class WaterBallon : public DynamicObject
{
private:
	int waterLength { 1 };	//물줄기
	CharacterColor color;

	ULONGLONG charAnimationTick;		//풍선 애니메이션 교체용 변수

	MapData* mapData{ nullptr };

	Direction::DirectionVar printDirCount{ 0,0,0,0 };	//방향에 따른 물줄기 길이
	vector<ObjectData::POSITION> hitObjectPos;			//피격 오브젝트 위치
	vector<ObjectData::POSITION> hitWaterBallonstPos;	//피격 물풍선 위치

	ObjectData::POSITION mapPos{ 0 };		//맵 정보

	AttackArea attackArea{ {-1,-1}, -1, -1, -1, -1 };	//공격범위에대한 정보

	int state{ WaterBallonState::DEFAULT };		//물풍선의 상태값

	//물줄기 길이 설정
	void SetExplosiontDir(const int x, const int y, const int dir, int& dirCount);	//폭발범위 설정
public:
	WaterBallon(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap,const int& waterLength);
	~WaterBallon();

	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);
	void  BoomRender(HDC hDC, HDC memDc, const int printBoomImgCount, const int direction);
	
	void GetMapData(MapData* mapData);

	const int GetState();

	void SetExplosionState();

	ObjectData::POSITION GetMapPos();
	vector<ObjectData::POSITION> GetHitObjectPos();
	vector<ObjectData::POSITION> GetHitWaterBallonsPos();

	void SetColor(CharacterColor color);
	CharacterColor GetColor() const;

	const AttackArea& GetAttackArea() const;
private:
	bool CheckmDelay(const int delayTime, ULONGLONG& tick);

};



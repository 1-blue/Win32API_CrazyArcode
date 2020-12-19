#pragma once
#include "DynamicObject.h"

class WaterBallon : public DynamicObject
{
private:
	ULONGLONG charAnimationTick;
	ULONGLONG deadlineTick;

	MapData mapData;

	Diraction::DirectionVar printDirCount{ 0,0,0,0 };

	bool isEffect{ false };
	bool isAlive{ true };

	void SetEffect4Dir();	//폭발범위 설정
public:
	WaterBallon(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap);
	~WaterBallon();

	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);
	void  BoomRender(HDC hDC, HDC memDc, const int printBoomImgCount, const int direction);
	

	void GetMapData(const MapData& mapData);

	const bool GetIsAlive();
private:
	bool CheckmDelay(const int delayTime, ULONGLONG& tick);
};



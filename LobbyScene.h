#pragma once
#include "DataStruct.h"

class LobbyScene
{
public:
	static int redImageNumber;
	static int blueImageNumber;
	static int mapImageNumber;
	static bool isStart;

private:
	string name;
	ObjectData::POSITION pos{ 0 ,0 };
	ObjectData::SIZE size{ 0 ,0 };
	HBITMAP hBitmap{ NULL };

	int hNumber{ 0 };		//가로이미지수
	int vNumber{ 0 };		//세로이미지수
	POINT cursorPos{ 0,0 };	//현재 마우스위치값저장할변수
	int imageNumber{ 0 };	//연속된 이미지중에 출력할 이미지 번호

	int imageWidth{ 0 };	//이미지 하나의 가로 길이
	int imageHeight{ 0 };	//이미지 하나의 세로 길이

	int printhNumber{ 0 };	//출력될 이미지 가로 번호
	int printvNumber{ 0 };	//출력될 이미지 세로 번호

public:
	LobbyScene(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap);
	~LobbyScene();
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);
	static bool IsStart();

};


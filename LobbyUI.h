#pragma once
#include "DataStruct.h"

class LobbyUI
{
public:
	//굳이 이렇게 할 필요가 있나 싶다. 클릭하면 그 값 리턴해서 object 매니저에서 관리하면 해결될 문젠데;;
	//뭔말인지는 알겠는데 이제 gameManager에서 사용하는데 굳이 GetSet만들고 gameMananger에서 주고받고하는것보단 이렇게하는게 낫지않나생각함
	//게임메니저는 전체총괄이라 Lobby의 데이터를 주고받는 용도로 사용하는건 별로인것같음 object매니저는 상관없을것같긴한데
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
	LobbyUI(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap);
	~LobbyUI();
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);
	static bool IsStart();

};


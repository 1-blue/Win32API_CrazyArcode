#pragma once
#include "DynamicObject.h"

class LobbyUI : public DynamicObject
{
public:
	//이거 조금많이 이상하다고 생각하는데
	//서로다른오브젝트끼리 값을 공유해야하는상황이 생겨서 추가함.. 좋은방법있으면 수정할필요있어보임
	//클릭을 했을때 다른오브젝트객체에 값을 변화시켜줘야해서추가

	//굳이 이렇게 할 필요가 있나 싶다. 클릭하면 그 값 리턴해서 object 매니저에서 관리하면 해결될 문젠데;;
	static int redImageNumber;
	static int blueImageNumber;
	static int mapImageNumber;
	static bool isStart;

public:
	LobbyUI(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap);
	~LobbyUI();
	virtual void Input();
	virtual void Update();
	virtual void Render(HDC hDC, HDC memDc);
	static bool IsStart();

};


#pragma once
#include <Windows.h>
#include <string>

using namespace std;

constexpr auto SSSS = 8;	
constexpr auto CURSOR_WIDTH		= 33;
constexpr auto CURSOR_HEIGHT	= 36;

//사용이유 : 이미지로 마우스 선택하면 클릭위치가 이미지 좌측하단이라 맞춰주기위함
//마우스 위치가져오는것은 여러군데 사용할거고 사용할때마다 적는것보단 적어야할코드가 어느정도 정해져있어서 매크로로 만들고 사용
#define GET_CURSOR_POSITION(point) \
GetCursorPos(&point);\
ScreenToClient(hWnd, &point);\
point.y -= CURSOR_HEIGHT;

typedef struct
{
	string name;		//이미지명
	HBITMAP hBitmap;	//출력할 비트맵
	int objType;		//오브젝트타입
	int x;				//임시 출력 x포지션
	int y;				//임시 출력 y포지션
	int kinds;			//단일, 가로. 세로 구분
	int number;			//이미지수
	int interval;		//간격

}ImageData, * pImageData;

namespace ObjectData
{
	typedef struct Position
	{
		int x;
		int y;

	}POSITION, * pPOSITION;

	typedef struct Size
	{
		int width;
		int height;

	}SIZE, * pSIZE;

	enum
	{
		NONE,
		HORIZONTAL,
		VERTICAL
	};
}
namespace GameStage
{
	enum
	{
		LOBBY,
		INGAME
	};
}

namespace CharacterSelect
{
	enum
	{
		BAZZI,
		DIZNI,
		RANDOM
	};
}

namespace MapSelect
{
	enum
	{
		MAP1,
		MAP2
	};
}

typedef struct
{
	int redCharacterNumber;
	int blueCharacterNumber;
	int mapNumber;
}SelectData, * pSelectData;
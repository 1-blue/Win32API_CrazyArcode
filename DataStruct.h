#pragma once
#include <Windows.h>
#include <string>
#include <list>
#include <vector>
#include <queue>

using namespace std;

constexpr auto WND_WIDTH = 800;
constexpr auto WND_HEIGHT = 600;
constexpr auto IMAGE_DATA_LENGTH = 7;
constexpr auto STATS_DATA_LENGTH = 7;
constexpr auto CURSOR_WIDTH = 33;
constexpr auto CURSOR_HEIGHT = 36;
constexpr auto PLAYER_NUMBER = 2;

//사용이유 : 이미지로 마우스 선택하면 클릭위치가 이미지 좌측하단이라 맞춰주기위함
//마우스 위치가져오는것은 여러군데 사용할거고 사용할때마다 적는것보단 적어야할코드가 어느정도 정해져있어서 매크로로 만들고 사용
#define GET_CURSOR_POSITION(point) \
GetCursorPos(&point);\
ScreenToClient(hWnd, &point);
//point.y -= CURSOR_HEIGHT;

typedef struct
{
	string name;		//이미지명
	HBITMAP hBitmap;	//출력할 비트맵
	int objType;		//오브젝트타입
	int x;				//임시 출력 x포지션
	int y;				//임시 출력 y포지션
	int hNumber;		//가로이미지수
	int vNumber;		//세로이미지수
}ImageData, *pImageData;

//캐릭터데이터
typedef struct
{
	int bNum;
	int bLength;
	int speed;
	int bNumMax;
	int bLengthMax;
	int speedMax;
}CharacterStatsData, * pCharacterStatsData;

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
	enum CharacterSelect
	{
		BAZZI,
		DIZNI,
		RANDOM
	};
}

namespace CharacterColor
{
	enum
	{
		RED,
		BLUE
	};
}


namespace Diraction
{
	enum
	{
		TOP,
		RIGHT,
		BOTTOM,
		LEFT
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

typedef struct
{
	string name;
	string path;
	int data[13][15];
}MapData, * pMapData;

typedef struct
{
	int mapWidth[255][255];
}Map, *pMap;

namespace Objects
{
	enum
	{
		BLANK,
		BLOCK,
		WALL
	};
}

namespace WaterBallonKinds
{
	enum
	{
		BALLON,
		CENTER,
		LEFT_END,
		LEFT_MID,
		TOP_END,
		TOP_MID,
		RIGHT_END,
		RIGHT_MID,
		BOTTOM_END,
		BOTTOM_MID
	};
}

typedef struct
{
	bool isAttack;
	int isColor;
	POINT pos;

}Attack, *pAttack;

typedef struct ClickEventStruct
{
	string name;
	bool isRight;

}ClickEvent, * pClickEvent;

/*
물풍선 이미지 저장순서

풍선
center
left end
left mid
top end
top mid
right end
right mid
bottom end
bottom mid
*/
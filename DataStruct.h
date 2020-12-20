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

//맵의 블록수
constexpr auto MAP_WIDTH_SIZE = 15;
constexpr auto MAP_HEIGHT_SIZE = 11;

//최대최소이동가능포지션
constexpr auto MOVE_MIN_X = 20;
constexpr auto MOVE_MAX_X = 580;
constexpr auto MOVE_MIN_Y = 20;
constexpr auto MOVE_MAX_Y = 500;

//한블럭크기
constexpr auto BLOCK_X = 40;
constexpr auto BLOCK_Y = 47;
constexpr auto SIZE_TUNING = 20;	//이거는 블록위치에 덮여서 출력되야할 사이즈조정을 위한거.. 설명하기 애매해서 보면알수있음

//오차범위 (비껴서 앞으로 갈때)
constexpr auto PERMIT_RANGE = 15;

//사용이유 : 이미지로 마우스 선택하면 클릭위치가 이미지 좌측하단이라 맞춰주기위함
//마우스 위치가져오는것은 여러군데 사용할거고 사용할때마다 적는것보단 적어야할코드가 어느정도 정해져있어서 매크로로 만들고 사용
#define GET_CURSOR_POSITION(point) \
GetCursorPos(&point);\
ScreenToClient(hWnd, &point);
//point.y -= CURSOR_HEIGHT;

typedef struct
{
	int name;		//이미지명
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

		bool operator==(const Position& pos)
		{
			if (this->x == pos.x && this->y == pos.y)
				return true;
			return false;
		}

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
		INGAME_LOADING,
		INGAME,
		INGAME_EXITING
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

namespace CharacterName
{
	enum
	{
		BAZZI,
		DIZNI
	};
}

namespace Direction
{
	enum
	{
		TOP,
		RIGHT,
		BOTTOM,
		LEFT,
		CENTER
	};

	typedef struct Dir
	{
		int north{ 0 };	//북
		int south{ 0 };	//남
		int east{ 0 };	//동
		int west{ 0 };	//서

	} DirectionVar;
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
	enum
	{
		STATIC,
		DYNAMIC,
		BUTTON,
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
	ObjectData::Position pos;

}Attack, *pAttack;

typedef struct ClickEventStruct
{
	int name;
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

typedef struct
{
	string name;		//이미지명
	HBITMAP hBitmap;	//출력할 비트맵
	int hNumber;		//가로이미지수
	int vNumber;		//세로이미지수
	int imageWidth;		//이미지 하나의 가로 길이
	int imageHeight;	//이미지 하나의 세로 길이
}Img, * pImg;

typedef struct
{
	int state;		//현재상태
	ObjectData::Position prevPos;				//이전위치
	ObjectData::Position lastWaterBallonPos;	//마지막물풍선위치
	bool isRevisit;								//마지막물풍선에서 범위밖으로 나갔는지 여부
	int trappedPrintvNumber;	//trapped 출력할 가로이미지번호
	int trappedPrinthNumber;	//trapped 출력할 세로이미지번호
	int diePrintvNumber;		//die 출력할 가로이미지번호
	int diePrinthNumber;		//die 출력할 세로이미지번호
	ULONGLONG time;		//시간저장할변수
	bool isAttackPossible;		//공격가능여부
	bool isMoveable;			//이동가능여부

}CharacterValues, *pCharacterValues;

namespace State
{
	enum
	{
		NORMAL,
		TRAPPED,
		DIE
	};
}
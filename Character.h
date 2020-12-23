#pragma once
#include "DynamicObject.h"

class Character : public DynamicObject
{
private:
	CharacterStatsData stats{ 0 };	//캐릭터의 정보.. 물풍선개수, 속도 등을 가지고있음
	Img trappedImage;				//trapped이미지 관련 변수들 저장
	Img dieImage;					//die이미지 관련 변수들 저장

	int color{ -1 };			//플레이어 색깔
	int characterName{ -1 };	//플레이어 캐릭터 이름
	int dir;					//플레이어 이동방향
	int prevDir;				//이전이동방향
	int state;					//현재상태
	int waterBallonNumber;		//놓여진 물풍선 개수

	bool isRevisit;				//마지막물풍선에서 범위밖으로 나갔는지 여부
	bool isAttackPossible;		//공격가능여부
	bool isMoveable;			//이동가능여부

	POINT printPos{ 0, 0 };						//여러개 이미지중에서 출력할 위치
	ObjectData::Position prevPos;				//이전위치
	ObjectData::Position lastWaterBallonPos;	//마지막물풍선위치
	Attack attack{ false, -1, 0, 0 };			//공격관련 변수들 저장
	
	ULONGLONG charAnimationTick;	//움직임 애니메이션 변수
	ULONGLONG deathTime;			//죽음애니메이션 변수

	list<ObjectData::Position> waterBallonPos;
	list<ItemData> itemPos;

	AttackArea attackArea{ {-1, -1}, -1, -1, -1, -1 };	//터지는 물풍선에 대한 정보,, 좌표, top, right, bottom, left

public:
	Character(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap, CharacterStatsData characterStats);
	~Character();
	void Init();

	virtual void Input();
	virtual void Update();
	ObjectData::Position LateUpdate(const list<Obj*>& inGameObjects);		//업데이트한 데이터보고 변경할거 변경
	virtual void Render(HDC hDC, HDC memDc);
	void GetDefaultImage(const pImageData trappedImage, const pImageData dieImage);		//trapped, die이미지 가져와서 저장

	bool CheckmDelay(ULONGLONG& animationTick, const int delayTime);
	void SetWaterBallonPos(list<ObjectData::Position> waterBallonPos);	//물풍선 위치 가져오기
	void SetItemPos(list<ItemData> itemPos);				//아이템 위치 가져오기
	Attack& GetAttack();			//공격관련 데이터전송
	void SettingBallonNumber();

	const int GetWaterBallonLength();
	void SetAttackArea(const AttackArea& attackArea);
	void CheckTrappedCollision(Character* character);	//trapped상태에서 충돌했는지검사
	void SetState(int state);
	int GetColor();

	void WaterBallonNumberUP();	//물풍선 개수 UP
	void WaterBallonLengthUP();	//물풍선 길이 UP
	void SpeedUP();		//캐릭터 속도 UP

private:
	void SettingAttackPos();	//물풍선 위치 세팅(지정된 영역에만 설치되게)
	bool OverlapCheck();		//중복설치체크
	void MapImmovableArea();	//맵이동제한
	void StaticObjectmmovableArea(const list<Obj*>& inGameObjectVector);	//블럭과 벽이동제한
	void WaterBallonImmovableArea();	//물풍선이동제한
	void Trapped();						//물풍선 맞을경우 실행
	void CheckBombArea();
	void TrappedAnimation();
	void DieAnimation();


};
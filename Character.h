#pragma once
#include "DynamicObject.h"

class Character : public DynamicObject
{
private:
	CharacterStatsData stats{ 0 };	//캐릭터의 정보.. 물풍선개수, 속도 등을 가지고있음
	Img trappedImage;		//trapped이미지 관련 변수들 저장
	Img dieImage;			//die이미지 관련 변수들 저장

	int color{ -1 };				//플레이어 색깔
	int characterName{ -1 };		//플레이어 캐릭터 이름
	int dir{ Direction::TOP };		//플레이어 이동방향
	POINT printPos{ 0, 0 };			//여러개 이미지중에서 출력할 위치
	Attack attack{ false, -1, 0, 0 };	//공격관련 변수들 저장
	CharacterValues characterValue;		//캐릭터 관련 변수들 저장.. 이거 나중에 캐릭터멤버변수로 바꾸기

	int prevDir{ Direction::TOP };
	ULONGLONG charAnimationTick = GetTickCount64();

	list<ObjectData::Position> waterBallonPos;

public:
	Character(const int name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap, CharacterStatsData characterStats);
	~Character();
	void Init();

	virtual void Input();
	virtual void Update();
	void LateUpdate(const list<Obj*>& inGameObjectVector);		//업데이트한 데이터보고 변경할거 변경
	virtual void Render(HDC hDC, HDC memDc);
	void GetDefaultImage(const pImageData trappedImage, const pImageData dieImage);		//trapped, die이미지 가져와서 저장

	void Manual();
	bool CheckmDelay(ULONGLONG& animationTick, const int delayTime);
	void SetWaterBallonList(list<ObjectData::Position> waterBallon);	//물풍선 위치 가져오기
	Attack& GetAttack();			//공격관련 데이터전송
	void SettingBallonNumber(int color);

	const int GetWaterBallonBLength();
	void UPBallonNumber();	//물풍선 개수 UP
	void UPBallonLength();	//물풍선 길이 UP
	void UPSetSpeed();		//캐릭터 속도 UP
private:
	void SettingAttackPos();	//물풍선 위치 세팅(지정된 영역에만 설치되게)
	void OverlapCheck();		//중복설치체크
	void MapImmovableArea();	//맵이동제한
	void StaticObjectmmovableArea(const list<Obj*>& inGameObjectVector);	//블럭과 벽이동제한
	void WaterBallonImmovableArea();	//물풍선이동제한
	void Trapped();						//물풍선 맞을경우 실행

};
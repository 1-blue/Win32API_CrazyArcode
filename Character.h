#pragma once
#include "DynamicObject.h"

class Character : public DynamicObject
{
private:
	CharacterStatsData characterStats{ 0 };	//캐릭터의 정보.. 물풍선개수, 속도 등을 가지고있음
	Img trappedImage;		//trapped이미지 관련 변수들 저장
	Img dieImage;			//die이미지 관련 변수들 저장

	int color{ -1 };				//플레이어 색깔 enum값으로 저장
	int characterName{ -1 };			//플레이어 이름 enum값으로 저장
	int dir{ Diraction::TOP };		//플레이어 이동방향
	POINT printPos{ 0, 0 };			//여러개 이미지중에서 출력할 위치
	Attack attack{ false, -1, 0, 0 };	//공격관련 변수들 저장

	int prevDir{ Diraction::TOP };
	ULONGLONG charAnimationTick = GetTickCount64();

	CharacterValues redValue;	//red캐릭터 관련 변수들 저장
	CharacterValues blueValue;	//blue캐릭터 관련 변수들 저장

	list<ObjectData::Position> waterBallonPos;	

public:
	Character(const string name, const ObjectData::POSITION pos, const ObjectData::SIZE size, int hNumber, int vNumber, HBITMAP hBitmap, CharacterStatsData characterStats);
	~Character();

	virtual void Input();
	virtual void Update();
	void LateUpdate(const list<Obj*>& inGameObjectVector);		//업데이트한 데이터보고 변경할거 변경
	virtual void Render(HDC hDC, HDC memDc);
	void GetDefaultImage(const pImageData trappedImage, const pImageData dieImage);		//trapped, die이미지 가져와서 저장

	void Manual();
	bool CheckmDelay(ULONGLONG& animationTick, const int delayTime);
	void SetWaterBallonList(list<ObjectData::Position> waterBallon);	//물풍선 위치 가져오기
	Attack& GetAttack();			//공격관련 데이터전송

private:
	void SettingAttackPos();	//물풍선 위치 세팅(지정된 영역에만 설치되게)
	void OverlapChack();		//중복설치체크
	void MapImmovableArea();	//맵이동제한
	void StaticObjectmmovableArea(const list<Obj*>& inGameObjectVector);	//블럭과 벽이동제한
	void WaterBallonImmovableArea();	//물풍선이동제한
	void Trapped();						//물풍선 맞을경우 실행

};


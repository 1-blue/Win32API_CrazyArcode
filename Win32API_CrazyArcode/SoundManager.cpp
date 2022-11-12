#include "SoundManager.h"
#include "DataStruct.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

SoundManager* SoundManager::instance = nullptr;


SoundManager* SoundManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new SoundManager();

		mciSendString("open Sound/installationBallon.wav alias installationBallon", 0, 0, 0);
		mciSendString("open Sound/mouseOverlap.wav alias mouseOverlap", 0, 0, 0);
		mciSendString("open Sound/explosionBallon.wav alias explosionBallon", 0, 0, 0);
		mciSendString("open Sound/pickupItem.mp3 alias pickupItem", 0, 0, 0);
		mciSendString("open Sound/explodeCharacter.mp3 alias explodeCharacter", 0, 0, 0);
	}

	return instance;
}

void SoundManager::ReleaseInstance()
{
	delete instance;
}

void SoundManager::PlaySoundTrack(BGM bgm)
{
	switch (bgm)
	{
	case BGM::ROOM:
		PlaySound("Sound/Crazy-Arcade-BGM-Room.wav", NULL, SND_ASYNC | SND_LOOP);
		break;
	case BGM::PATRIT:
		PlaySound("Sound/Crazy-Arcade-BGM-Patrit.wav", NULL, SND_ASYNC | SND_LOOP);
		break;
	}
}

void SoundManager::PlayEffectSound(EFFECTSOUND effectSound)
{
	switch (effectSound)
	{
	case EFFECTSOUND::INSTALL:
		mciSendString("play installationBallon from 0", 0, 0, 0);
		break;
	case EFFECTSOUND::OVERLAP_BUTTON:
		mciSendString("play mouseOverlap from 0", 0, 0, 0);
		break;
	case EFFECTSOUND::EXPLOSION:
		mciSendString("play explosionBallon from 0", 0, 0, 0);
		break;
	case EFFECTSOUND::PICKUP_ITEM:
		mciSendString("play pickupItem from 0", 0, 0, 0);
		break;
	case EFFECTSOUND::EXPLODECHARACTER:
		mciSendString("play explodeCharacter from 0", 0, 0, 0);
		break;
	}
}

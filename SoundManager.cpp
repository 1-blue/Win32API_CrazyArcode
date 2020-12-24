#include "SoundManager.h"
#include "DataStruct.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

SoundManager* SoundManager::instance = nullptr;


SoundManager* SoundManager::GetInstance()
{
	if (instance == nullptr) 
		instance = new SoundManager();

	return instance;
}

void SoundManager::ReleaseInstance()
{
	delete instance;
}

void SoundManager::PlaySoundTrack(const int number)
{
	switch (number)
	{
	case 1:
		PlaySound("Sound/Crazy-Arcade-BGM-Room.wav", NULL, SND_ASYNC | SND_LOOP);
		break;
	case 2:
		PlaySound("Sound/Crazy-Arcade-BGM-Patrit.wav", NULL, SND_ASYNC | SND_LOOP);
		break;
	}
}

void SoundManager::PlayEffectSound(const int number)
{
	switch (number)
	{
	case 1:
		mciSendString("play Sound/installationBallon.wav from 0", 0, 0, 0);
		break;
	case 2:
		mciSendString("play Sound/mouseOverlap.wav from 0", 0, 0, 0);
		break;
	}
}

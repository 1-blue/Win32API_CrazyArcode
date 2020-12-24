#pragma once
class SoundManager
{
private:
	static SoundManager* instance;

	SoundManager() {};
	~SoundManager() {};
public:
	static SoundManager* GetInstance();
	static void ReleaseInstance();

	void PlaySoundTrack(const int number);
	void PlayEffectSound(const int number);
};


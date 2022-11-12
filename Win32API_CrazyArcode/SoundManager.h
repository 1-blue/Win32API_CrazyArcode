#pragma once
enum class BGM : int;
enum class EFFECTSOUND : int;
class SoundManager
{
private:
	static SoundManager* instance;

	SoundManager() {};
	~SoundManager() {};
public:
	static SoundManager* GetInstance();
	static void ReleaseInstance();

	void PlaySoundTrack(BGM bgm);
	void PlayEffectSound(EFFECTSOUND effectSound);
};
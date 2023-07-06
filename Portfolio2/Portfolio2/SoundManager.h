#pragma once
#include "SingletonBase.h"
// 윈도우 내장 라이브러리 (재생)
// 시간 / v사운드 -> PlaySound()
#include <mmsystem.h>
// mciSendString()이라는 함수를 사용하기 위해
#include <mciapi.h>

#pragma comment(lib, "Winmm.lib")
class SoundManager : public SingletonBase<SoundManager>
{
private:

public:
	HRESULT init(void);
	// MP3
	void addMp3FileWithKey(string key, string fileName);
	// WAV
	void addWaveFileWithKey(string key, string fileName);
	// 효과음
	void playEffentSoundWave(char* fileName);
	// MP3 재생
	void playSoundWithKey(string key);
	// 정지
	void stopMp3WithKey(string key);

	SoundManager() {};
	~SoundManager() {};
};


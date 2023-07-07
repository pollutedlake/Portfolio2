#pragma once
#include "SingletonBase.h"
// ������ ���� ���̺귯�� (���)
// �ð� / v���� -> PlaySound()
#include <mmsystem.h>
// mciSendString()�̶�� �Լ��� ����ϱ� ����
#include <mciapi.h>

#pragma comment(lib, "Winmm.lib")
class SoundManager : public SingletonBase<SoundManager>
{
private:
	FMOD::System* pSystem;
	FMOD::Sound* pSound;
	FMOD::Channel* pChannel;
	//typedef map<string, FMOD::Sound*> mapSoundList;
	//typedef map<string, FMOD::Sound*>::iterator mapSoundIter;

	//mapSoundList _mSoundList;

public:
	HRESULT init(void);
	void release(void);
	// MP3
	void addMp3FileWithKey(string key, string fileName);
	// WAV
	void addWaveFileWithKey(string key, string fileName);
	// ȿ����
	void playEffectSoundWave(char* fileName);
	// MP3 ���
	void playSoundWithKey(string key);
	// ����
	void stopMp3WithKey(string key);

	void addSoundFMOD(const char* fileName);
	void playSoundFMOD();
	unsigned int getSoundLength();
	unsigned int getCurrentPos();
	bool isPlaying();

	SoundManager() {};
	~SoundManager() {};
};


#include "Stdafx.h"
#include "SoundManager.h"

HRESULT SoundManager::init(void)
{
    if (FMOD::System_Create(&pSystem) != FMOD_OK)
    {
        return E_ABORT;
    }
    if (pSystem->init(512, FMOD_INIT_NORMAL, 0) != FMOD_OK)
    {
        return E_ABORT;
    }
    
    return S_OK;
}

void SoundManager::release(void)
{
    pSystem->release();
}

void SoundManager::addMp3FileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type mpegvideo alias ";
    string finalQuery = first + fileName + end + key;
    const char* str = finalQuery.c_str();

    // mciSendString() : 장치에 특정 명령어를 전송하여 구동시키는 함수
    // ㄴ 문자열 명령어, 반환값을 알려줄 명령어, 반환될 길이, 핸들콜백
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::addWaveFileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type waveautio alias ";
    string finalQuery = first + fileName + end + key;
    const char* str = finalQuery.c_str();

    // mciSendString() : 장치에 특정 명령어를 전송하여 구동시키는 함수
    // ㄴ 문자열 명령어, 반환값을 알려줄 명령어, 반환될 길이, 핸들콜백
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::playEffectSoundWave(char* fileName)
{
    /*
    // PlaySound() : TEXT("파일 이름.wav"),
    // 파일명을 시용하면 NULL != 해당 인스턴스 핸들
    // fdwSount (옵션 | 옵션 | 옵션)

    SND_ASYNC : 재생하면서 다음코드를 실행
    ㄴ 비동기 플래그

    SND_LOOP : 반복 재생

    SND_NODEFAULT : 지정한 경로에 파일이 없어도 경고음을 재생하지 않는다.
    */
    PlaySound(fileName, NULL, SND_ASYNC);
}

void SoundManager::playSoundWithKey(string key)
{
    string first = "play ";
    string finalQuery = first + key;

    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::stopMp3WithKey(string key)
{
    string first = "stop ";
    string finalQuery = "";
    finalQuery = first + key;

    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::addSoundFMOD(const char* fileName)
{
    pSystem->createSound(fileName, FMOD_DEFAULT, 0, &pSound);
}

void SoundManager::playSoundFMOD()
{
    pSystem->playSound(pSound, NULL, false, &pChannel);
}

unsigned int SoundManager::getSoundLength()
{
    unsigned int length;
    pSound->getLength(&length, FMOD_TIMEUNIT_MS);
    return length;
}

unsigned int SoundManager::getCurrentPos()
{
    unsigned int position;
    pChannel->getPosition(&position, FMOD_TIMEUNIT_MS);
    return position;
}

bool SoundManager::isPlaying()
{
    bool playing;
    pChannel->isPlaying(&playing);
    return playing;
}

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

    // mciSendString() : ��ġ�� Ư�� ��ɾ �����Ͽ� ������Ű�� �Լ�
    // �� ���ڿ� ��ɾ�, ��ȯ���� �˷��� ��ɾ�, ��ȯ�� ����, �ڵ��ݹ�
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::addWaveFileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type waveautio alias ";
    string finalQuery = first + fileName + end + key;
    const char* str = finalQuery.c_str();

    // mciSendString() : ��ġ�� Ư�� ��ɾ �����Ͽ� ������Ű�� �Լ�
    // �� ���ڿ� ��ɾ�, ��ȯ���� �˷��� ��ɾ�, ��ȯ�� ����, �ڵ��ݹ�
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::playEffectSoundWave(char* fileName)
{
    /*
    // PlaySound() : TEXT("���� �̸�.wav"),
    // ���ϸ��� �ÿ��ϸ� NULL != �ش� �ν��Ͻ� �ڵ�
    // fdwSount (�ɼ� | �ɼ� | �ɼ�)

    SND_ASYNC : ����ϸ鼭 �����ڵ带 ����
    �� �񵿱� �÷���

    SND_LOOP : �ݺ� ���

    SND_NODEFAULT : ������ ��ο� ������ ��� ������� ������� �ʴ´�.
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

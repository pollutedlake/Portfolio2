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
    for (int i = 0; i < 20; i++)
    {
        pChannel[i]->stop();
    }
    deleteAll();
}

FMOD::Sound* SoundManager::addSoundFMOD(string key, const char* fileName)
{
    FMOD::Sound* sound = findSound(key);
    if (sound) return sound;

    if (pSystem->createSound(fileName, FMOD_DEFAULT, 0, &sound) != FMOD_OK)
    {
        SAFE_DELETE(sound);
        return nullptr;
    }
    _mSoundList.insert(make_pair(key, sound));

    return sound;
}

FMOD::Sound* SoundManager::findSound(string key)
{
    auto iter = _mSoundList.find(key);
    if (iter != _mSoundList.end())
    {
        return iter->second;
    }
    return nullptr;
}

void SoundManager::playSoundFMOD(string key)
{
    if(findSound(key) == nullptr) return;
    bool playing;
    for (int i = 0; i < 20; i++)
    {
        pChannel[i]->isPlaying(&playing);
        if (!playing)
        {
            pSystem->playSound(findSound(key), NULL, false, &pChannel[i]);
            return;
        }
    }
}

void SoundManager::stopSoundFMOD(string key)
{
    FMOD::Sound* sound;
    char findName[256];
    findSound(key)->getName(findName, 256);
    char soundName[256];
    bool playing = false;
    for (int i = 0; i < 20; i++)
    {
        pChannel[i]->isPlaying(&playing);
        if (!playing)
        {
            continue;
        }
        pChannel[i]->getCurrentSound(&sound);
        sound->getName(soundName, 256);
        if (!strcmp(soundName, findName))
        {
           pChannel[i]->stop();
            return;
        }
    }
}

unsigned int SoundManager::getSoundLength(string key)
{
    unsigned int length;
    findSound(key)->getLength(&length, FMOD_TIMEUNIT_MS);
    return length;
}

unsigned int SoundManager::getCurrentPos(string key)
{
    unsigned int position = 0;
    char findName[256];
    findSound(key)->getName(findName, 256);
    FMOD::Sound* sound;
    char soundName[256];
    bool playing = false;
    for (int i = 0; i < 20; i++)
    {
        pChannel[i]->isPlaying(&playing);
        if (!playing)
        {
            continue;
        }
        pChannel[i]->getCurrentSound(&sound);
        sound->getName(soundName, 256);
       if (!strcmp(soundName, findName))
       {
            pChannel[i]->getPosition(&position, FMOD_TIMEUNIT_MS);
            return position;
       }
    }
    return position;
}

bool SoundManager::isPlaying()
{
    bool playing = false;
    for (int i = 0; i < 20; i++)
    {
        pChannel[i]->isPlaying(&playing);
        if (playing)
        {
            return playing;
        }
    }
    return playing;
}

void SoundManager::stopAllSoundFMOD()
{
    bool playing = false;
    for (int i = 0; i < 20; i++)
    {
        pChannel[i]->isPlaying(&playing);
        if (!playing)
        {
            continue;
        }
        pChannel[i]->stop();
    }
}

bool SoundManager::deleteAll()
{
    auto iter = _mSoundList.begin();
    /*for (; iter != _mSoundList.end();)
    {
        if (iter->second != NULL)
        {
            iter->second->release();
            iter = _mSoundList.erase(iter);
        }
        else
        {
            ++iter;
        }
    }*/
    _mSoundList.clear();
    return true;
}

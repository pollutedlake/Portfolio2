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

void SoundManager::update(void)
{
    pSystem->update();
}

void SoundManager::addMp3FileWithKey(string key, string fileName)
{
	string first = "open \"";
	string end = "\" type mpegvideo alias ";
	string finalQuery = first + fileName + end + key;
	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}

void SoundManager::addWaveFileWithKey(string key, string fileName)
{
    string first = "open \"";
    string end = "\" type waveautio alias ";
    string finalQuery = first + fileName + end + key;
    const char* str = finalQuery.c_str();
    mciSendString(str, NULL, 0, NULL);
}

void SoundManager::playEffectSoundWave(char* fileName)
{
    PlaySound(fileName, NULL, SND_ASYNC);
}

void SoundManager::playSoundWithKey(string key)
{
	string first = "play ";
	string finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}

FMOD::Sound* SoundManager::addSoundFMOD(string key, const char* fileName)
{
    FMOD::Sound* sound = findSound(key);
    if (sound) return sound;

    if (pSystem->createSound(fileName, FMOD_DEFAULT, 0, &sound) != FMOD_OK)
    {
        cout << pSystem->createSound(fileName, FMOD_DEFAULT, 0, &sound) << "\t" << key << endl;
        SAFE_DELETE(sound);
        return nullptr;
    }
    _mSoundList.insert(make_pair(key, sound));

    return sound;
}

FMOD::Sound* SoundManager::addSoundFMOD(string key, const char* fileName, bool loop)
{
	FMOD::Sound* sound = findSound(key);
	if (sound) return sound;
    if(loop)
    {
	    if (pSystem->createSound(fileName, FMOD_LOOP_NORMAL, 0, &sound) != FMOD_OK)
	    {
			cout << pSystem->createSound(fileName, FMOD_DEFAULT, 0, &sound) << "\t" << key << endl;
			SAFE_DELETE(sound);
	    	return nullptr;
	    }
    }
    else
    {
		if (pSystem->createSound(fileName, FMOD_DEFAULT, 0, &sound) != FMOD_OK)
		{
			cout << pSystem->createSound(fileName, FMOD_DEFAULT, 0, &sound) << "\t" << key << endl;
			SAFE_DELETE(sound);
			return nullptr;
		}
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
    cout << "no sound" << endl;
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
            FMOD_RESULT fr;
            if (fr = pSystem->playSound(findSound(key), NULL, false, &pChannel[i]))
            {
                cout << fr << endl;
            }
            return;
        }
    }
    cout << "no channel" << endl;
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
    _mSoundList.clear();
    return true;
}

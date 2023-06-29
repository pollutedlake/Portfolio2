#include "Stdafx.h"
#include "AnimationManager.h"

HRESULT AnimationManager::init(void)
{
	return E_NOTIMPL;
}

void AnimationManager::release(void)
{
}

void AnimationManager::update(void)
{
}

Animation* AnimationManager::findAnimation(string key)
{
	return nullptr;
}

bool AnimationManager::deleteAnimation(string key)
{
	return false;
}

bool AnimationManager::deleteAll()
{
	return false;
}

void AnimationManager::addAnimation(string key, char* imageKey, int fps, bool reverse, bool loop)
{
}

void AnimationManager::addAnimation(string key, char* imageKey, int fps, bool reverse, bool loop, Animation* anim)
{
}

void AnimationManager::addAnimation(string key, char* imageKey, int start, int end, int fps, bool reverse, bool loop)
{
}

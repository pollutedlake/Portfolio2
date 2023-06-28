#pragma once
#include "SingletonBase.h"
#include "Animation.h"

class AnimationManager : public SingletonBase<AnimationManager>
{
private:
	map<string, Animation*> _animationMap;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	
	Animation* findAnimation(string key);
	bool deleteAnimation(string key);
	bool deleteAll();
	void addAnimation(string key, char* imageKey, int fps, bool reverse, bool loop);
	void addAnimation(string key, char* imageKey, int fps, bool reverse, bool loop, Animation* anim);
	void addAnimation(string key, char* imageKey, int start, int end, int fps, bool reverse, bool loop);
};


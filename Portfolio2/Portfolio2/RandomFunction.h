#pragma once
#include "SingletonBase.h"

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{
		srand(GetTickCount());
	}
	~RandomFunction() {}

	HRESULT init(void) { return S_OK; }

	// 0 ~ num - 1
	inline int getInt(int num)
	{
		return rand() % num;
	}
	// fromNum ~ toNum
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	// 소수 float 생성
	float getFloat(void)
	{
		return (float)rand() / (float)RAND_MAX;
	}

	// 0 ~ num
	float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}

	// fromNum ~ toNum
	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toNum - fromNum) + fromNum);
	}
};
#pragma once
#include "Character.h"
class Player : public Character
{
private:

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render()

};


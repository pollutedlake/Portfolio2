#pragma once
#include "SingletonBase.h"
#include "Player.h"

class PartyManager : public SingletonBase<PartyManager>
{
private:
	vector<Player*> _playerList;

public:
	HRESULT init(void);
	void release(void);
};


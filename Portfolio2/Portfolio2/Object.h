#pragma once
class Object
{
protected:
	int _type;			// object type
	POINT _tilePos;		// ��ġ�� Ÿ��

public:
	int getType() { return _type; }
	POINT getTilePos() {return _tilePos;}

	Object() {}
	~Object() {}
};


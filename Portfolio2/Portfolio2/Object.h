#pragma once
class Object
{
protected:
	int _type;			// object type
	POINT _tilePos;		// 위치한 타일

public:
	int getType() { return _type; }
	POINT getTilePos() {return _tilePos;}

	Object() {}
	~Object() {}
};


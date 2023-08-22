#pragma once
class Object
{
protected:
	int _type;
	POINT _tilePos;

public:
	int getType() { return _type; }
	POINT getTilePos() {return _tilePos;}

	Object() {}
	~Object() {}
};


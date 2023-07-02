#pragma once
#include "SingletonBase.h"
class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
public:
	typedef map<string, GameNode*> mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	GameNode* _currentScene;
	mapSceneList _sceneMap;
	
public:

	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	void addScene(string sceneName, GameNode* scene);
	HRESULT changeScene(string sceneName);

	SceneManager() {}
	~SceneManager() {}
};


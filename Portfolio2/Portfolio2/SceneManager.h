#pragma once
#include "SingletonBase.h"
#include "GameNode.h"
#include "TitleScene.h"
#include "ScenarioScene.h"

class SceneManager : public SingletonBase<SceneManager>
{
private:
	GameNode* _currentScene;
	map<string, GameNode*> _sceneMap;
	
public:

	HRESULT init(void);
	void update(void);
	void release(void);
	void render(HDC hdc);

	void addScene(string sceneName, GameNode* scene);
	HRESULT changeScene(string sceneName);

	SceneManager() {}
	~SceneManager() {}
};


#pragma once
#include "GameNode.h"
#include "TitleScene.h"
#include "ScenarioScene.h"

enum class Scene
{
	TITLE,
	SCENARIO,
	SCENENUM
};

class SceneManager : public GameNode
{
private:
	TitleScene* _titleScene;
	ScenarioScene* _scenarioScene;
	Scene _scene;
	
public:

	HRESULT init(void);
	void update(void);
	void release(void);
	void render(HDC hdc);

	void changeScene(Scene scene);

	SceneManager() {}
	~SceneManager() {}
};


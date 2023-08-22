#pragma once
#include "../FrameWork/DesignPattern/SingletonBase.h"
class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
public:
	typedef map<string, GameNode*> mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	GameNode* _currentScene;
	GameNode* _exScene;
	mapSceneList _sceneMap;
	GImage* _blackImg;
	GImage* _whiteImg;
	
public:

	HRESULT init(void);
	void update(void);
	void release(void);
	void render(void);

	void addScene(string sceneName, GameNode* scene);
	HRESULT loadingScene();
	HRESULT changeScene(string sceneName);

	void setExScene(GameNode* exScene) { _exScene = exScene; }
	void returnScene() { _currentScene = _exScene; }

	void fadeOutWhite(int start, int cur, int end);
	void fadeInWhite(int start, int cur, int end);
	void fadeOutBlack(int start, int cur, int end);
	void fadeInBlack(int start, int cur, int end);
	void fadeOutImage(int start, int cur, int end, string key);
	void fadeInImage(int start, int cur, int end, string key);
	
	SceneManager() {}
	~SceneManager() {}
};


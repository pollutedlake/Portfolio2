#include "../FrameWork/PCH/Stdafx.h"
#include "./SceneManager.h"
#include "../FrameWork/GameNode/GameNode.h"
#include "../Scene/TitleScene.h"
#include "../Scene/ScenarioScene.h"
#include "../Scene/StoryScene.h"
#include "../Scene/EndingScene.h"
#include "../Scene/BossBattleScene.h"
#include "../Scene/WorldMapScene.h"
#include "../Scene/ShopScene.h"
#include "../Scene/LoadingScene.h"
#include "../Scene/BattleScene.h"
#include "../Scene/LoadScene.h"

HRESULT SceneManager::init(void)
{
    SCENEMANAGER->addScene("Title", new TitleScene);
    SCENEMANAGER->addScene("Scenario", new ScenarioScene);
    SCENEMANAGER->addScene("Story", new StoryScene);
    SCENEMANAGER->addScene("Ending", new EndingScene);
    SCENEMANAGER->addScene("BossBattle", new BossBattleScene);
    SCENEMANAGER->addScene("WorldMap", new WorldMapScene);
    SCENEMANAGER->addScene("Shop", new ShopScene);
    SCENEMANAGER->addScene("Loading", new LoadingScene);
    SCENEMANAGER->addScene("Battle", new BattleScene);
    SCENEMANAGER->addScene("Load", new LoadScene);
    _whiteImg = IMAGEMANAGER->findImage("White");
    _blackImg = IMAGEMANAGER->findImage("Black");
    _currentScene = nullptr;
    return S_OK;
}

void SceneManager::update(void)
{
    if (_currentScene != nullptr)
    {
        _currentScene->update();
    }
}

void SceneManager::release(void)
{
    for (auto iter = _sceneMap.begin(); iter != _sceneMap.end();)
    {
        if (iter->second != nullptr)
        {
            iter = _sceneMap.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
    _sceneMap.clear();
}

void SceneManager::render(void)
{
	if (_currentScene != nullptr)
	{
		_currentScene->render();
	}
}



void SceneManager::addScene(string sceneName, GameNode* scene)
{
    if (scene != nullptr)
    {
        _sceneMap.insert(make_pair(sceneName, scene));
    }
}

HRESULT SceneManager::loadingScene()
{
    auto iter = ((LoadingScene*)(_sceneMap.find("Loading")->second));
    cout << DATAMANAGER->getSceneIdx() << endl;
    if (DATAMANAGER->getSceneIdx() == DATAMANAGER->getSceneList(DATAMANAGER->getScenario()).size())
    {
        DATAMANAGER->setSceneIdx(0);
        DATAMANAGER->setBattleIdx(0);
        DATAMANAGER->setMaxScenario(DATAMANAGER->getMaxScenario() + 6);
        if (DATAMANAGER->getScenario() == 75)
        {
			_currentScene = _sceneMap.find("Title")->second;
			_currentScene->init();
			//iter->init("Title");
        }
        else
        {
            _currentScene = _sceneMap.find("Scenario")->second;
            _currentScene->init();
        }
    }
    else
    {
        iter->init(DATAMANAGER->getSceneList(DATAMANAGER->getScenario())[DATAMANAGER->getSceneIdx()]);
        DATAMANAGER->setSceneIdx(DATAMANAGER->getSceneIdx() + 1);
        _currentScene = iter;
    }
    return S_OK;
}

HRESULT SceneManager::changeScene(string sceneName)
{
    auto iter = _sceneMap.find(sceneName);
    if (iter->second == _currentScene)
    {
        return S_OK;
    }
    if (SUCCEEDED(iter->second->init()))
    {
        _currentScene = iter->second;
        return S_OK;
    }
    return E_FAIL;
}

void SceneManager::fadeOutWhite(int start, int cur, int end)
{
    _whiteImg->alphaRender(_currentScene->getMemDC(), cur > end ? 255 : 255.0f / (float)(end - start) * (float)(cur - start));
}

void SceneManager::fadeInWhite(int start, int cur, int end)
{
    _whiteImg->alphaRender(_currentScene->getMemDC(), cur > end ? 0 : 255.0f - 255.0f / (float)(end - start) * (float)(cur - start));
}

void SceneManager::fadeOutBlack(int start, int cur, int end)
{
    _blackImg->alphaRender(_currentScene->getMemDC(), cur > end ? 255 : 255.0f / (float)(end - start) * (float)(cur - start));
}

void SceneManager::fadeInBlack(int start, int cur, int end)
{
    _blackImg->alphaRender(_currentScene->getMemDC(), cur > end ? 0 : 255.0f - 255.0f / (float)(end - start) * (float)(cur - start));
}

void SceneManager::fadeOutImage(int start, int cur, int end, string key)
{
    IMAGEMANAGER->findImage(key)->alphaRender(_currentScene->getMemDC(), cur > end ? 255 : 255.0f / (float)(end - start) * (float)(cur - start));
}

void SceneManager::fadeInImage(int start, int cur, int end, string key)
{  
    IMAGEMANAGER->findImage(key)->alphaRender(_currentScene->getMemDC(), cur > end ? 0 : 255.0f - 255.0f / (float)(end - start) * (float)(cur - start));
}

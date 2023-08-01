#include "Stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"
#include "TitleScene.h"
#include "ScenarioScene.h"
#include "StoryScene.h"
#include "EndingScene.h"
#include "BossBattleScene.h"
#include "WorldMapScene.h"
#include "ShopScene.h"
#include "LoadingScene.h"
#include "BattleScene.h"

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
	/*_currentScene->release();
	SAFE_DELETE(_currentScene);*/
    for (auto iter = _sceneMap.begin(); iter != _sceneMap.end();)
    {
        if (iter->second != nullptr)
        {
            //iter->second->release();
            //SAFE_DELETE(iter->second);
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
        iter->init("Title");
    }
    else
    {
        iter->init(DATAMANAGER->getSceneList(DATAMANAGER->getScenario())[DATAMANAGER->getSceneIdx()]);
    }
    DATAMANAGER->setSceneIdx(DATAMANAGER->getSceneIdx() + 1);
    _currentScene = iter;
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

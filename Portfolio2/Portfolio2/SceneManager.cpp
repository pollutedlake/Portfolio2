#include "Stdafx.h"
#include "SceneManager.h"

HRESULT SceneManager::init(void)
{
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
	_currentScene->release();
	SAFE_DELETE(_currentScene);
    for (auto iter = _sceneMap.begin(); iter != _sceneMap.end();)
    {
        if (iter->second != nullptr)
        {
            iter->second->release();
            SAFE_DELETE(iter->second);
            iter = _sceneMap.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
    _sceneMap.clear();
}

void SceneManager::render(HDC hdc)
{
	if (_currentScene != nullptr)
	{
		_currentScene->render(hdc);
	}
}



void SceneManager::addScene(string sceneName, GameNode* scene)
{
    if (scene != nullptr)
    {
        _sceneMap.insert(make_pair(sceneName, scene));
    }
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

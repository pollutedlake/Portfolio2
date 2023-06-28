#include "Stdafx.h"
#include "SceneManager.h"

HRESULT SceneManager::init(void)
{
    _titleScene = new TitleScene;
    _scenarioScene = new ScenarioScene;
    _titleScene->init();
    _scenarioScene->init();
    _scene = Scene::TITLE;
    return S_OK;
}

void SceneManager::update(void)
{
    switch (_scene)
    {
    case Scene::TITLE:
        _titleScene->update();
        break;
    case Scene::SCENARIO:
        _scenarioScene->update();
        break;
    }
}

void SceneManager::release(void)
{
    SAFE_DELETE(_titleScene);
    SAFE_DELETE(_scenarioScene);
}

void SceneManager::render(HDC hdc)
{
    switch (_scene)
    {
    case Scene::TITLE:
        _titleScene->render(hdc);
        break;
    case Scene::SCENARIO:
        _scenarioScene->render(hdc);
        break;
    }
}

void SceneManager::changeScene(Scene scene)
{
    _scene = scene;
}

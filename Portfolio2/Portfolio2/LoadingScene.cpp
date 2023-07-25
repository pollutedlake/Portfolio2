#include "Stdafx.h"
#include "LoadingScene.h"

HRESULT LoadingScene::init(string prevScene, string nextScene)
{
    _frame = 0;
    _prevScene = prevScene;
    _nextScene = nextScene;
    _loadingImgIndex = RND->getFromIntTo(1, 41);
    return S_OK;
}

void LoadingScene::release(void)
{
}

void LoadingScene::update(void)
{
    _frame++;
    if (_frame > 100)
    {
        SCENEMANAGER->changeScene(_nextScene);
    }
}

void LoadingScene::render(void)
{
    IMAGEMANAGER->findImage("LoadingSceneBG")->frameRender(getMemDC(), WINSIZE_X / 2 - IMAGEMANAGER->findImage("LoadingSceneBG")->getFrameWidth() / 2, WINSIZE_Y / 2 - IMAGEMANAGER->findImage("LoadingSceneBG")->getFrameHeight() / 2, _loadingImgIndex, 0);
}

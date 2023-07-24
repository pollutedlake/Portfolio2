#include "Stdafx.h"
#include "LoadingScene.h"

HRESULT LoadingScene::init(string prevScene, string nextScene)
{
    _frame = 0;
    _prevScene = prevScene;
    _nextScene = nextScene;
    wsprintf(_loadingImage, "LoadingScene");
    _loadingImage[strlen("LoadingScene")] = RND->getFromIntTo(1, 9) + 48;
    _loadingImage[strlen("LoadingScene") + 1] = '\0';
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
    IMAGEMANAGER->findImage(_loadingImage)->render(getMemDC(), WINSIZE_X / 2 - IMAGEMANAGER->findImage(_loadingImage)->getWidth() / 2, WINSIZE_Y / 2 - IMAGEMANAGER->findImage(_loadingImage)->getHeight() / 2);
}

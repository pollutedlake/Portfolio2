#include "Stdafx.h"
#include "LoadingScene.h"

HRESULT LoadingScene::init(string prevScene, string nextScene)
{
    _frame = 0;
    _prevScene = prevScene;
    _nextScene = nextScene;
    wsprintf(_loadingImage, "LoadingScene%d", RND->getFromIntTo(1, 11));
    /*int loadingImageN = RND->getFromIntTo(1, 11);
    if (loadingImageN > 9)
    {
        _loadingImage[strlen("LoadingScene")] = loadingImageN / 10 + 48;
        _loadingImage[strlen("LoadingScene") + 1] = loadingImageN % 10 + 48;
        _loadingImage[strlen("LoadingScene") + 2] = '\0';
    }
    else
    {
        _loadingImage[strlen("LoadingScene")] = loadingImageN + 48;
        _loadingImage[strlen("LoadingScene") + 1] = '\0';
    }*/
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

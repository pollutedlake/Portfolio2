#include "Stdafx.h"
#include "WorldMapScene.h"

HRESULT WorldMapScene::init(void)
{
	_frame = 0;
	_camera = new Camera();
	_camera->init();
	_camera->setPosition({(LONG)(IMAGEMANAGER->findImage("WorldMap")->getWidth() / 2), (LONG)(IMAGEMANAGER->findImage("WorldMap")->getHeight() / 2)});
	_camera->setLimitRight(IMAGEMANAGER->findImage("WorldMap")->getWidth() - WINSIZE_X / 2);
	_camera->setLimitBottom(IMAGEMANAGER->findImage("WorldMap")->getHeight() - WINSIZE_Y / 2);
	return S_OK;
}

void WorldMapScene::update(void)
{
	_camera->update();
	_cameraPos = _camera->getPosition();
	_frame++;
}

void WorldMapScene::render(void)
{
	IMAGEMANAGER->findImage("WorldMap")->render(getMemDC(), WINSIZE_X / 2 - _cameraPos.x, WINSIZE_Y / 2 - _cameraPos.y);
	IMAGEMANAGER->findImage("WorldMapMarker")->alphaFrameRender(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 255), WINSIZE_Y / 2 - (_cameraPos.y - 210), (_frame / 5) % 10, 0, 128);
	IMAGEMANAGER->findImage("SaladinMark")->render(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 295), WINSIZE_Y / 2 - (_cameraPos.y - 230));
	IMAGEMANAGER->findImage("WorldMapInfo")->render(getMemDC());//, 0, 0, IMAGEMANAGER->findImage("WorldMapInfo")->getWidth(), IMAGEMANAGER->findImage("WorldMapInfo")->getHeight(), 0, 0, IMAGEMANAGER->findImage("WorldMapInfo")->getWidth(), IMAGEMANAGER->findImage("WorldMapInfo")->getHeight());
	IMAGEMANAGER->findImage("WorldMapFlag")->render(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 255), WINSIZE_Y / 2 - (_cameraPos.y - 210));
	IMAGEMANAGER->findImage("WorldMapTeam")->frameRender(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 255), WINSIZE_Y / 2 - (_cameraPos.y - 210), (_frame / 5) % 5, 0);
	IMAGEMANAGER->findImage("WorldMapSaladin")->render(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 255), WINSIZE_Y / 2 - (_cameraPos.y - 210));
	IMAGEMANAGER->findImage("MouseCursor")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
}

void WorldMapScene::release(void)
{
	_camera->release();
	SAFE_DELETE(_camera);
}

#include "Stdafx.h"
#include "BossBattleScene.h"

HRESULT BossBattleScene::init(void)
{
	_backGroundImg = IMAGEMANAGER->findImage("BossBattleBG");
	_tableImg = IMAGEMANAGER->findImage("Table");
	_mouseCursorImg = IMAGEMANAGER->findImage("MouseCursor");
	_camera = new Camera();
	_camera->init();
	_camera->setPosition({(LONG)(_backGroundImg->getWidth() * 1.5 / 2), (LONG)(_backGroundImg->getHeight() * 1.5 / 2)});
	_camera->setLimitRight(_backGroundImg->getWidth() * 1.5 - WINSIZE_X / 2);
	_camera->setLimitBottom(_backGroundImg->getHeight() * 1.5 - WINSIZE_Y / 2);

	_saladin = new Saladin();
	_saladin->init();
	_saladin->setDir(LEFT);
	_saladin->setState(IDLE);
	_saladin->setTilePos({33, 40});
	_tileInfo[_saladin->getTilePos().y][_saladin->getTilePos().x] = SALADIN;

	_vermont = new Vermont();
	_vermont->init();
	_vermont->setDir(RIGHT);
	_vermont->setState(IDLE);
	_vermont->setTilePos({24, 40});
	_tileInfo[_vermont->getTilePos().y][_vermont->getTilePos().x] = VERMONT;
	_frame = 0;
	_debug = false;

	return S_OK;
}

void BossBattleScene::release(void)
{
	_camera->release();
	_saladin->release();
	SAFE_DELETE(_camera);
	SAFE_DELETE(_saladin);
}

void BossBattleScene::update(void)
{
	if (_frame == 0)
	{
		SOUNDMANAGER->playSoundFMOD("BossBattle");
	}
	_camera->update();
	_saladin->update();
	_vermont->update();
	_cameraPos = _camera->getPosition();
	_frame++;
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_debug = !_debug;
	}

	// 마우스커서가 위치한 타일 구하기
	_cursorTile.x = (_cameraPos.x - WINSIZE_X / 2 + _ptMouse.x) / TileWidth;
	_cursorTile.y = (_cameraPos.y - WINSIZE_Y / 2 + _ptMouse.y) / TileHeight;
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_tileInfo[_cursorTile.y][_cursorTile.x] == MOVABLE)
		{
			_saladin->setRoute(_aStar.findRoute(_saladin->getTilePos(), _cursorTile, _tileInfo, 90, 60));
			_saladin->setState(MOVE);
			_tileInfo[_saladin->getTilePos().y][_saladin->getTilePos().x] = MOVABLE;
			//_vermont->setRoute(_aStar.findRoute(_vermont->getTilePos(), _cursorTile, _tileInfo, 90, 60));
			//_vermont->setState(MOVE);
			//_tileInfo[_vermont->getTilePos().y][_vermont->getTilePos().x] = MOVABLE;
		}
		if (_tileInfo[_cursorTile.y][_cursorTile.x] == VERMONT)
		{
			if (_cursorTile.y - _saladin->getTilePos().y > 0)
			{
				_saladin->setDir(DOWN);
			}
			else if (_cursorTile.y - _saladin->getTilePos().y < 0)
			{
				_saladin->setDir(UP);
			}
			else
			{
				if (_cursorTile.x - _saladin->getTilePos().x > 0)
				{
					_saladin->setDir(RIGHT);
				}
				else if (_cursorTile.x - _saladin->getTilePos().x < 0)
				{
					_saladin->setDir(LEFT);
				}
			}
			_saladin->setState(ATTACK);
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SOUNDMANAGER->stopAllSoundFMOD();
		SCENEMANAGER->changeScene("Ending");
	}
}

void BossBattleScene::render(void)
{
	_backGroundImg->render(getMemDC(), WINSIZE_X / 2 - _cameraPos.x, WINSIZE_Y / 2 - _cameraPos.y, _backGroundImg->getWidth() * 1.5, _backGroundImg->getHeight() * 1.5, 0, 0, _backGroundImg->getWidth(), _backGroundImg->getHeight());
	IMAGEMANAGER->findImage("CursorTile")->alphaFrameRender(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - _cursorTile.x * TileWidth),
	WINSIZE_Y / 2 - (_cameraPos.y - _cursorTile.y * TileHeight), TileWidth, TileHeight, (_frame / 5) % IMAGEMANAGER->findImage("CursorTile")->getMaxFrameX(), 0, 128);
	_vermont->render(getMemDC(), { WINSIZE_X / 2 - (_cameraPos.x - _vermont->getTilePos().x * TileWidth),
	WINSIZE_Y / 2 - (_cameraPos.y - _vermont->getTilePos().y * TileHeight + TileHeight / 2 * 3) });
	_saladin->render(getMemDC(), {WINSIZE_X / 2 - (_cameraPos.x - _saladin->getTilePos().x * TileWidth),
	WINSIZE_Y / 2 - (_cameraPos.y - _saladin->getTilePos().y * TileHeight + TileHeight / 2 * 3)});
	_tableImg->render(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - 1110), WINSIZE_Y / 2 - (_cameraPos.y - 1180), _tableImg->getWidth(), _tableImg->getHeight() * 1.5, 0, 0, _tableImg->getWidth(), _tableImg->getHeight());
	_mouseCursorImg->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, (_frame / 5) % 7, 0);
	if (_debug)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		HPEN hOldPen = (HPEN)SelectObject(getMemDC(), hPen);
		for (int i = 0; i < TileRowN; i++)
		{
			LineMake(getMemDC(), WINSIZE_X / 2 - _cameraPos.x, WINSIZE_Y / 2 - (_cameraPos.y - TileHeight * (i + 1)), WINSIZE_X / 2 - (_cameraPos.x - 2400), WINSIZE_Y / 2 - (_cameraPos.y - TileHeight * (i + 1)));
		}
		for (int i = 0; i < TileColN; i++)
		{
			LineMake(getMemDC(), WINSIZE_X / 2 - (_cameraPos.x - TileWidth * (i + 1)), WINSIZE_Y / 2 - _cameraPos.y, WINSIZE_X / 2 - (_cameraPos.x - TileWidth * (i + 1)), WINSIZE_Y / 2 - (_cameraPos.y - 2700));
		}
		SelectObject(getMemDC(), hOldPen);
		DeleteObject(hPen);
		RECT saladinRect;
		saladinRect.left = WINSIZE_X / 2 - (_cameraPos.x - _saladin->getTilePos().x * TileWidth);
		saladinRect.right = WINSIZE_X / 2 - (_cameraPos.x - (_saladin->getTilePos().x + 1) * TileWidth);
		saladinRect.top = WINSIZE_Y / 2 - (_cameraPos.y - _saladin->getTilePos().y * TileHeight);
		saladinRect.bottom = WINSIZE_Y / 2 - (_cameraPos.y - (_saladin->getTilePos().y + 1) * TileHeight);
		for (int i = 0; i < TileRowN; i++)
		{
			for (int j = 0; j < TileColN; j++)
			{
				RECT rt;
				rt.left = WINSIZE_X / 2 - (_cameraPos.x - j * TileWidth);
				rt.right = WINSIZE_X / 2 - (_cameraPos.x - (j + 1) * TileWidth);
				rt.top = WINSIZE_Y / 2 - (_cameraPos.y - i * TileHeight);
				rt.bottom = WINSIZE_Y / 2 - (_cameraPos.y - (i + 1) * TileHeight);
				if(_tileInfo[i][j] == 0)
				{
					FillRect(getMemDC(), &rt, HBRUSH(RGB(0, 255, 0)));
				}
			}
		}
		FillRect(getMemDC(), &saladinRect, HBRUSH(RGB(255, 0, 0)));
	}
	char str[258];
	wsprintf(str, "%d, %d", _cursorTile.x, _cursorTile.y);
	TextOut(getMemDC(), 0, 0, str, strlen(str));
}

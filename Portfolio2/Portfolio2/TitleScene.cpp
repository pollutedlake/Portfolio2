#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{

	_titleBG = IMAGEMANAGER->findImage("TitleBG");
	_titleName = IMAGEMANAGER->findImage("TitleName");
	_titleEFX2 = IMAGEMANAGER->findImage("TitleEFX2");
	_titleEFX1 = IMAGEMANAGER->findImage("TitleEFX1");
	_titleEFX3 = IMAGEMANAGER->findImage("TitleEFX3");
	_titleEFX4 = IMAGEMANAGER->findImage("TitleEFX4");
	_titleButtons = IMAGEMANAGER->findImage("TitleButtons");
	_cursor = IMAGEMANAGER->findImage("MouseCursor");
	_frame = 0;
	_deltaTime = 0;
	_activeButton = -1;
	_fadeOutStartFrame = 0;
	_fadeOut = false;
	_videoShow = true;
	_pMediaControl = nullptr;
	_pMediaEvent = nullptr;
	_pGraphBuilder = nullptr;
	_pMediaSeeking = nullptr;
	for (int i = 0; i < 4; i++)
	{
		_buttonsRC[i] = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + _titleName->getHeight() / 2 + 50 + _titleButtons->getFrameHeight() * 3 / 2 * (i + 1), _titleButtons->getFrameWidth(), _titleButtons->getFrameHeight() * 3 / 2);
	}
	if(DATAMANAGER->getIntroVideo())
	{
		if(FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
		{
			cout << "CoInitializeEx Failed" << endl;
		}
		if(FAILED(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&_pGraphBuilder)))
		{
			cout << "CoCreateInstance Failed" << endl;
		}
		if (LoadVideo(L"Resources/Video/Opening.avi"))
		{
			cout << "Load Video" << endl;
		}
	}
	return S_OK;
}

void TitleScene::update(void)
{
	if (DATAMANAGER->getIntroVideo())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			DATAMANAGER->setIntroVideo(false);
			_pMediaControl->Stop();
		}
	}
	else
	{
		if (!SOUNDMANAGER->isPlaying() && !_fadeOut)
		{
			SOUNDMANAGER->playSoundFMOD("TitleScene");
		}
		_deltaTime++;
		_activeButton = -1;
		if(_deltaTime <= 286)
		{
			_titleEFX1->setFrameX((_deltaTime / 2) % 13);
			_titleEFX1->setFrameY(_deltaTime / 26);
		}
		else
		{
			if (_deltaTime % 5 == 0)
			{
				_frame++;
			}
		}
		if(!_fadeOut && _frame > 50)
		{
			for (int i = 0; i < 4; i++)
			{
				if (PtInRect(&_buttonsRC[i], _ptMouse))
				{
					_activeButton = i;
					break;
				}
			}
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				switch (_activeButton)
				{
				case 0:
					SOUNDMANAGER->stopSoundFMOD("TitleScene");
					SOUNDMANAGER->playSoundFMOD("TitleButton");
					_fadeOut = true;
					_fadeOutStartFrame = _frame;
					break;
				case 3:
					PostQuitMessage(0);
					break;
				}
			}
		}
		if(_fadeOut)
		{
			if (_frame > _fadeOutStartFrame + _titleEFX4->getMaxFrameX())
			{
				SCENEMANAGER->changeScene("Scenario");
			}
		}
	}
}

void TitleScene::render(void)
{
	if (DATAMANAGER->getIntroVideo())
	{
		//// (Assume that g_rcDest was calculated previously.)
		//HRGN rgnClient = CreateRectRgnIndirect(&rcSrc);
		//HRGN rgnVideo = CreateRectRgnIndirect(&rcDest);
		//CombineRgn(rgnClient, rgnClient, rgnVideo, RGN_DIFF);

		//// Paint on window.
		//HBRUSH hbr = GetSysColorBrush(COLOR_BTNFACE);
		//FillRgn(getMemDC(), rgnClient, hbr);

		//// Clean up.
		//DeleteObject(hbr);
		//DeleteObject(rgnClient);
		//DeleteObject(rgnVideo);

		//// Request the VMR to paint the video.
		//_pWindowless->RepaintVideo(_hWnd, getMemDC());
	}
	else
	{
		_titleBG->render(getMemDC());
		if(!_fadeOut)
		{
			if(_deltaTime <= 286)
			{
				_titleEFX1->frameRender(getMemDC(), WINSIZE_X / 2 - _titleEFX1->getFrameWidth() / 2, WINSIZE_Y / 2 - _titleEFX1->getFrameHeight() / 2);
			}
			else
			{
				_titleEFX3->frameRender(getMemDC(), WINSIZE_X / 2 - 10, WINSIZE_Y / 2 - _titleEFX4->getHeight() + 25, _frame % _titleEFX3->getMaxFrameX(), 1);
				_titleEFX2->alphaFrameRender(getMemDC(), WINSIZE_X / 2 - _titleEFX2->getFrameWidth() / 2, WINSIZE_Y / 2 - _titleEFX2->getFrameHeight() / 2, _frame % 6, (_frame / 6) % 6, 128);
				_titleName->alphaRender(getMemDC(), WINSIZE_X / 2 - _titleName->getWidth() / 2, WINSIZE_Y / 2 - _titleName->getHeight() / 2, _titleName->getWidth(), _titleName->getHeight(), 0, 0, _titleName->getWidth(), _titleName->getHeight(), _frame * 40 > 255 ? 255 : _frame * 5);
				if (_frame > 50)
				{
					for (int i = 0; i < 4; i++)
					{
						if (_activeButton == i)
						{
							_titleButtons->frameRender(getMemDC(), _buttonsRC[i].left, _buttonsRC[i].top, _titleButtons->getFrameWidth(), _titleButtons->getFrameHeight(), 0, i);
						}
						else
						{
							_titleButtons->frameRender(getMemDC(), _buttonsRC[i].left, _buttonsRC[i].top, _titleButtons->getFrameWidth(), _titleButtons->getFrameHeight(), 1, i);
						}
					}
					_cursor->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frame % 7, 0);
				}
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				_titleButtons->alphaFrameRender(getMemDC(), _buttonsRC[i].left, _buttonsRC[i].top, 0, i, _frame == _fadeOutStartFrame ? 255 : 255 / ((_frame - _fadeOutStartFrame)));
			}
			SCENEMANAGER->fadeOutBlack(_fadeOutStartFrame, _frame, _fadeOutStartFrame + _titleEFX4->getMaxFrameX() / 3);
			_titleEFX4->frameRender(getMemDC(), WINSIZE_X / 2 - _titleEFX4->getFrameWidth() / 2, WINSIZE_Y / 2 - _titleEFX4->getFrameHeight() / 2, _frame -_fadeOutStartFrame, 0);
		}
	}
	//for(int i = 0; i < 5; i++)
	//{
	//	IMAGEMANAGER->findImage("FireFly")->alphaFrameRender(getMemDC(), -IMAGEMANAGER->findImage("FireFly")->getFrameWidth() + IMAGEMANAGER->findImage("FireFly")->getFrameWidth() * i + (float)IMAGEMANAGER->findImage("FireFly")->getFrameWidth() / 31.f * (_frame % 31),
	//	WINSIZE_Y - IMAGEMANAGER->findImage("FireFly")->getFrameHeight(), _frame % 31, 0, 120);
	//}
}

void TitleScene::release(void)
{
	if (_pGraphBuilder)
	{
		_pGraphBuilder->Release();
	}
	if (_pMediaControl)
	{
		_pMediaControl->Release();
	}
	if (_pMediaEvent)
	{
		_pMediaEvent->Release();
	}
	if (_pMediaSeeking)
	{
		_pMediaSeeking->Release();
	}
	CoUninitialize();
}

HRESULT TitleScene::InitWindowlessVMR(HWND hwndApp, IGraphBuilder* pGraph, IVMRWindowlessControl** ppWc)
{
	if (!pGraph || !ppWc)
	{
		return E_POINTER;
	}
	IBaseFilter* pVmr = NULL;
	IVMRWindowlessControl* pWc = NULL;
	// Create the VMR. 
	HRESULT hr = CoCreateInstance(CLSID_VideoMixingRenderer, NULL,
		CLSCTX_INPROC, IID_IBaseFilter, (void**)&pVmr);
	if (FAILED(hr))
	{
		return hr;
	}

	// Add the VMR to the filter graph.
	hr = pGraph->AddFilter(pVmr, L"Video Mixing Renderer");
	if (FAILED(hr))
	{
		pVmr->Release();
		return hr;
	}
	// Set the rendering mode.  
	IVMRFilterConfig* pConfig;
	hr = pVmr->QueryInterface(IID_IVMRFilterConfig, (void**)&pConfig);
	if (SUCCEEDED(hr))
	{
		hr = pConfig->SetRenderingMode(VMRMode_Windowless);
		pConfig->Release();
	}
	if (SUCCEEDED(hr))
	{
		// Set the window. 
		hr = pVmr->QueryInterface(IID_IVMRWindowlessControl, (void**)&pWc);
		if (SUCCEEDED(hr))
		{
			hr = pWc->SetVideoClippingWindow(hwndApp);
			if (SUCCEEDED(hr))
			{
				*ppWc = pWc; // Return this as an AddRef'd pointer. 
			}
			else
			{
				// An error occurred, so release the interface.
				pWc->Release();
			}
		}
	}
	pVmr->Release();
	return hr;
}

bool TitleScene::LoadVideo(LPCWSTR videoFilePath)
{
	if(!_pGraphBuilder) return false;

	if (FAILED(_pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&_pMediaControl)))
	{
		cout << "MediaControl 실패" << endl;
	}
	if (FAILED(_pGraphBuilder->QueryInterface(IID_IMediaEvent, (void**)&_pMediaEvent)))
	{
		cout << "MediaEvent 실패" << endl;
	}
	if (FAILED(_pGraphBuilder->QueryInterface(IID_IMediaSeeking, (void**)&_pMediaSeeking)))
	{
		cout << "MediaSeeking 실패" << endl;
	}
	if(SUCCEEDED(InitWindowlessVMR(_hWnd, _pGraphBuilder, &_pWindowless)))
	{
		if (FAILED(_pGraphBuilder->RenderFile(videoFilePath, NULL)))
		{
			cout << "RenderFile Failed" << endl;
			return false;
		}
		else
		{
			long lWidth, lHeight;
			HRESULT hr = _pWindowless->GetNativeVideoSize(&lWidth, &lHeight, NULL, NULL);
			if (SUCCEEDED(hr))
			{
				// Set the source rectangle.
				SetRect(&rcSrc, 0, 0, lWidth, lHeight);

				// Get the window client area.
				GetClientRect(_hWnd, &rcDest);
				// Set the destination rectangle.
				SetRect(&rcDest, 0, 0, rcDest.right, rcDest.bottom);

				// Set the video position.
				hr = _pWindowless->SetVideoPosition(&rcSrc, &rcDest);
			}
			_pMediaControl->Run();
		}
	}

	return true;
}

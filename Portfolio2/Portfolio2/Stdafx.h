#pragma once
#pragma warning(disable : 4005)

#include<SDKDDKVER.h>

#define WIN32_LEAN_AND_MEAN
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

#pragma comment (lib, "msimg32.lib")
#pragma comment (lib, "fmod_vc.lib")

#include <windows.h>
#include "inc/fmod.hpp"
#include "inc/fmod_errors.h"
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>

#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <queue>
#include<map>
#include<string.h>
#include <unordered_map>
#include<cassert>
#include<bitset>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

// Singleton
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "FontManager.h"
#include "DialogManager.h"
#include "DataManager.h"

#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define DIALOGMANAGER DialogManager::getSingleton()
#define DATAMANAGER DataManager::getSingleton()

#define WINNAME					(LPTSTR)(TEXT("창세기전3 Part1"))
#define WINSTART_X				400
#define WINSTART_Y				100
#define WINSIZE_X				960
#define WINSIZE_Y				720
#define TILEWIDTH				40
#define TILEHEIGHT				30

#define PI                       3.141592
#define WINSTYLE				WS_CAPTION | WS_SYSMENU

// 매크로 함수
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

// 전역 변수
extern HINSTANCE				_hInstance;
extern HWND						_hWnd;
extern POINT					_ptMouse;

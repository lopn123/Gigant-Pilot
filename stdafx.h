#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <mciapi.h>
#include <string>
#include <time.h>
using namespace std;

#define g_device DXUTGetD3D9Device()
#define Vec3 D3DXVECTOR3
#define Vec2 D3DXVECTOR2
//다이렉트X는 디바이스(device)라는 개념을 사용한다
//이 디바이스는 프로그래머가 그래픽카드를 제어할수 있는 방법을 주는 녀석이라 생각하면 된다

#ifdef _DEBUG
#define DEBUG_LOG(log) cout << log << endl;
#else
#define DEBUG_LOG(log)
#endif
//using D3DXVECTOR2 Vec2;

const int WINSIZEX = 1600;
const int WINSIZEY = 900;

#include "cTexture.h"
#include "cImageManager.h"
#include "cUIManager.h"
#include "cRenderManager.h"
#include "cSceneManager.h"
#include "cKeyManager.h"
#include "cObjectManager.h"
#include "cSoundManager.h"
#include "cTimer.h"
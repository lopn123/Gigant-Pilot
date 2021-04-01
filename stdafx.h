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
//���̷�ƮX�� ����̽�(device)��� ������ ����Ѵ�
//�� ����̽��� ���α׷��Ӱ� �׷���ī�带 �����Ҽ� �ִ� ����� �ִ� �༮�̶� �����ϸ� �ȴ�

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
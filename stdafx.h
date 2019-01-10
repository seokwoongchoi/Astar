#pragma once

//#define FILE_SYSTEM_BINARY

//Windows
#include <Windows.h>
#include <assert.h>
#include <time.h>

//STL
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <chrono>
#include <algorithm>
using namespace std;

//DirectWrite
#include <d2d1_1.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

//DirectX 11
#include <dxgi1_2.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <d3dx10math.h>
#include <d3dx11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//ImGui
#include <imgui.h>
#include <imguiDx11.h>
#pragma comment(lib, "imgui.lib")

//FMOD
#include <FMOD\fmod.hpp>
#include <FMOD\fmod_errors.h>
#pragma comment(lib, "fmod_vc.lib")

//Macro Function
#define SAFE_RELEASE(p)			{ if (p) { (p)->Release(); (p)=nullptr;}}
#define SAFE_DELETE(p)			{ if (p) { delete (p); (p)=nullptr; } }
#define SAFE_DELETE_ARRAY(p)	{ if (p) { delete[] (p); (p)=nullptr; } }

//InputController
#define MAX_INPUT_KEY 255
#define MAX_INPUT_MOUSE 8

//Virtual Key Code
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5

typedef unsigned int uint;

//Main System
#include "./Framework/Core/Settings.h"
#include "./Framework/Core/Context.h"

//DirectX 11 Rapper Class
#include "./Framework/Core/D3D11/VertexLayout.h"
#include "./Framework/Core/D3D11/ConstantBufferDataType.h"
#include "./Framework/Core/D3D11/ConstantBuffer.h"
#include "./Framework/Core/D3D11/VertexBuffer.h"
#include "./Framework/Core/D3D11/IndexBuffer.h"
#include "./Framework/Core/D3D11/BaseShader.h"
#include "./Framework/Core/D3D11/VertexShader.h"
#include "./Framework/Core/D3D11/PixelShader.h"
#include "./Framework/Core/D3D11/RasterizerState.h"
#include "./Framework/Core/D3D11/BlendState.h"
#include "./Framework/Core/D3D11/RenderTexture.h"

//Utility
#include "./Framework/Utility/Xml.h"
#include "./Framework/Utility/Path.h"

//Math
#include "./Framework/Math/Math.h"
#include "./Framework/Math/BoundBox.h"

//Subsystem
#include "./Framework/Core/Subsystem/Graphics.h"
#include "./Framework/Core/Subsystem/DirectWrite.h"
#include "./Framework/Core/Subsystem/Timer.h"
#include "./Framework/Core/Subsystem/Input.h"
#include "./Framework/Core/Subsystem/Audio.h"
#include "./Framework/Core/Subsystem/ResourceManager.h"
#include "./Framework/Core/Subsystem/SceneManager.h"
#include "./Framework/Core/Subsystem/EffectManager.h"
#include "./Framework/Core/Subsystem/ColliderManager.h"

//Component
#include "./Framework/Component/Transform.h"

//Resource
#include "./Framework/Resource/Texture2D.h"
#include "./Framework/Resource/Mesh.h"
#include "./Framework/Resource/SpriteAnimation.h"
#include "./Framework/Resource/Shader.h"
#include "./Framework/Resource/AudioClip.h"
#include "./Framework/Resource/Effect.h"

#include "./Framework/Utility/GenericGeometry.h"



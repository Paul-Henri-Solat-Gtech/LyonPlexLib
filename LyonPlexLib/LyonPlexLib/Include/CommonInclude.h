#pragma once

// THIS IS FOR BOTH PCH -> LIB & APP

//First Priority
#include <iostream>
#include <string>
#include <windows.h>
#include <dxgi1_6.h>
#include <wrl.h>

#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <Audio.h>

//Lib DX12
#pragma comment(lib, "d3d12.lib")
#include <d3d12.h>
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <dxgi1_4.h>
#include <dxgidebug.h>  

//Namespace to shortcut variables
using namespace Microsoft::WRL;
using namespace DirectX;

//Second Priority
#include "../../ExternalLib/DirectXTK12-main/Src/d3dx12.h"
#include "../../ExternalLib/DirectXTK12-main/Src/PlatformHelpers.h"

//CLASS OF LYONPLEX
#include "WindowPlex.h"
#include "GameManager.h"



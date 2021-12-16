#pragma once

#define NOMINMAX

//D3DLibrary
#include <d3dcompiler.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dcompiler.lib")

//Base
#include <iostream>
#include <Windows.h>
#include <assert.h>
#include <memory>
#include <typeinfo>
#include <filesystem>
#include <vector>
#include <unordered_map>
#include <guiddef.h>
#include <iomanip>
#include <sstream>

//Subsystem
#include "Subsystem/D3D11_Base.h"


//D3D11Wrapper Class
#include "D3D11/ID3D11.h"

//Utillity
#include "Utillity/defines.h"
#include "Utillity/GUID_Creator.h"

//Tool
#include "Core/Tool.h"

//Manager
#include "Manager/SubsystemManager.h"

//Settings
#include "Setting/Window.h"

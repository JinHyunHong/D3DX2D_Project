#pragma once

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
#include "Header/defines.h"

//STL
#include <vector>
#include <unordered_map>


//Tool
#include "Core/Tool.h"

//Manager
#include "Manager/SubsystemManager.h"

//Settings
#include "Setting/Window.h"
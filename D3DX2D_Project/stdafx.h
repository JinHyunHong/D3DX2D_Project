#pragma once

#define NOMINMAX

// D3DLibrary
#include <d3dcompiler.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "d3dcompiler.lib")

// Base
#include <iostream>
#include <Windows.h>
#include <assert.h>
#include <memory>
#include <typeinfo>
#include <filesystem>
#include <vector>
#include <map>
#include <unordered_map>
#include <guiddef.h>
#include <iomanip>
#include <sstream>
#include <random>
#include <chrono>
#include <mutex>

// Utillity
#include "Utillity/defines.h"
#include "Utillity/Xml.h"
#include "Utillity/GUID_Creator.h"
#include "Utillity/Math/Math.h"

// Core
#include "Core/Core.h"

// Tool
#include "Core/Tool.h"

// Manager
#include "Manager/SubsystemManager.h"
#include "Manager/SceneManager.h"
#include "Manager/ResourceManager.h"

// Settings
#include "Setting/Window.h"

// Subsystem
#include "Manager/Subsystem/D3D11_Base.h"
#include "Manager/Subsystem/Timer.h"
#include "Manager/Subsystem/Renderer/Renderer.h"

// D3D11Wrapper Class
#include "D3D11/Object.h"
#include "D3D11/D3D11.h"

#include "D3D11/Vertex/D3D11_Vertex.h"
#include "D3D11/Vertex/D3D11_Geometry.h"

#include "D3D11/InputAssembler/D3D11_VertexBuffer.h"
#include "D3D11/InputAssembler/D3D11_IndexBuffer.h"
#include "D3D11/InputAssembler/D3D11_InputLayout.h"

#include "D3D11/Shader/D3D11_Shader.h"
#include "D3D11/Shader/D3D11_ConstantBuffer.h"
#include "D3D11/Shader/D3D11_SamplerState.h"
#include "D3D11/Shader/D3D11_Texture.h"

#include "D3D11/Rasterizer/D3D11_RasterizerState.h"
#include "D3D11/Rasterizer/D3D11_Viewport.h"

#include "D3D11/OutputMerger/D3D11_BlendState.h"

#include "D3D11/D3D11_Pipeline.h"


// Resource
#include "Resource/Animation.h"


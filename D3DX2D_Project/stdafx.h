#pragma once

#define NOMINMAX

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
#include <string>
#include "resource.h"


// D3DLibrary
#include <d3dcompiler.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dcompiler.lib")


// DirectX XTK
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <SimpleMath.h>

// TinyXML
#include "Assets/Source/Tiny_XML/Xml.h"

// Utillity
#include "Utillity/defines.h"
#include "Utillity/Math/Math.h"
#include "Utillity/GUID_Creator.h"

// Core
#include "Core/Core.h"

// Tool
#include "Core/Tool.h"

// Settings
#include "Setting/Window.h"

// Manager
#include "Manager/SubsystemManager.h"
#include "Manager/ResourceManager.h"

// Subsystem
#include "Manager/Subsystem/Timer.h"
#include "Manager/Subsystem/InputManager.h"
#include "Manager/Subsystem/D3D11_Base.h"
#include "Manager/Subsystem/Renderer/Renderer.h"
#include "Manager/Subsystem/SceneManager.h"

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
#include "Resource/Tile.h"


#pragma once
#include "stdafx.h"

typedef unsigned int uint;

#define SAFE_DELETE(p)			{ if (p) { delete (p); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p)	{ if (p) { delete[] (p); (p) = nullptr; } }
#define SAFE_RELEASE(p)			{ if (p) { (p)->Release(); (p) = nullptr; } }

#define CLEAR_VECTOR(p)			{ p.clear(); p.shrink_to_fit(); }
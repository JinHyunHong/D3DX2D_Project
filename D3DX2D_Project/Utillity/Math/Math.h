#pragma once
#include "stdafx.h"

namespace Math
{
	static std::random_device rd;
	static std::mt19937 mt(rd());

	
	static constexpr float PI = 3.14159265359f; // PI
	static constexpr float PI_2 = 6.28318530718f; // PI * 2
	static constexpr float PI_DIV_2 = 1.57079632679f; // PI / 2
	static constexpr float PI_DIV_4 = 0.78539816339f; // PI / 4
	static constexpr float TO_DEG = 180.0f / PI; // 디그리
	static constexpr float TO_RAD = PI / 180.f; // 라디안

	inline auto Random(const int& min, const int& max) -> const int
	{
		return std::uniform_int_distribution<int>{min, max}(mt);
	}

	inline auto Random(const float& min, const float& max) -> const float
	{
		return std::uniform_real_distribution<float>{min, max}(mt);
	}

	inline auto Vec3_Abs(const D3DXVECTOR3& lhs, const D3DXVECTOR3& rhs) -> const D3DXVECTOR3
	{
		return D3DXVECTOR3(abs(lhs.x - rhs.x), abs(lhs.y - rhs.y), abs(lhs.z - rhs.z));
	}
}